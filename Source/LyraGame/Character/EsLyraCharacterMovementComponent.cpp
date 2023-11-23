// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EsLyraCharacterMovementComponent.h"

#include "LyraCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

FNetworkPredictionData_Client* UEsLyraCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if (ClientPredictionData == nullptr)
	{
		UEsLyraCharacterMovementComponent* MutableThis = const_cast<UEsLyraCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Es(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f; 
	}
	return ClientPredictionData;
}

UEsLyraCharacterMovementComponent::UEsLyraCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Safe_bWantsToTeleport = false;
	Safe_bWantsToWallRun = false;
	TeleportStartTime = 0.f;
}

void UEsLyraCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
	ESCharacterOwner = Cast<ALyraCharacter>(GetOwner());
}

/**
 *  Update the character state in PerformMovement right before doing the actual position change
 **********************************************************************************************************/
void UEsLyraCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	//Teleport
	const bool bAuthProxy = CharacterOwner->HasAuthority() && !CharacterOwner->IsLocallyControlled();
	if(Safe_bWantsToTeleport && CanTeleport())
	{
		if(!bAuthProxy || GetWorld()->GetTimeSeconds() - TeleportStartTime > AuthTeleportCooldownDuration)
		{
			PerformTeleport();
			Safe_bWantsToTeleport = false;		
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Error with the client values (Cheating)"));
		}
	}
	
	// Wall Run	
	TryWallRun();	
	
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

/**
 *  PhysCustom including Phys functions for each CustomMovementMode
 **********************************************************************************************************/
void UEsLyraCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	switch (CustomMovementMode)
	{	
	case CMOVE_WallRun:
		PhysWallRun(deltaTime, Iterations);
		break;	
	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"))
	}
}

/**
 *  
 **********************************************************************************************************/
void UEsLyraCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode,
	uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);	
}

/**
 *  Event notification when client receives correction data from the server, before applying the data
 **********************************************************************************************************/
void UEsLyraCharacterMovementComponent::OnClientCorrectionReceived(FNetworkPredictionData_Client_Character& ClientData,
																   float TimeStamp, FVector NewLocation, FVector NewVelocity, UPrimitiveComponent* NewBase, FName NewBaseBoneName,
																   bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode)
{
	Super::OnClientCorrectionReceived(ClientData, TimeStamp, NewLocation, NewVelocity, NewBase, NewBaseBoneName,
									  bHasBase, bBaseRelativePosition,
									  ServerMovementMode);

	UE_LOG(LogTemp, Warning, TEXT("On Client Correction Received"));
}

/**
 *  Unpack compressed flags from a saved move and set state accordingly
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToTeleport = (Flags & FSavedMove_Es::FLAG_Teleport) != 0;
	Safe_bWantsToWallRun = (Flags & FSavedMove_Es::FLAG_WallRun) != 0;
}

#pragma region Teleport
/**
 *  Player canTeleport while walking or midair
 **********************************************************************************************************/
bool UEsLyraCharacterMovementComponent::CanTeleport() const
{
	return IsWalking() || IsFalling();
}

/**
 *  Teleport the character by TeleportImpulse. Use velocity if want to avoid sweep
 **********************************************************************************************************/
void UEsLyraCharacterMovementComponent::PerformTeleport()
{	
	TeleportStartTime = GetWorld()->GetTimeSeconds();	
	
	const FVector ForwardVector = UpdatedComponent->GetForwardVector();
	FHitResult Hit;

	SafeMoveUpdatedComponent(ForwardVector * TeleportImpulse, UpdatedComponent->GetComponentRotation(), true, Hit, ETeleportType::None);

	SetMovementMode(MOVE_Falling);
}

/**
 *  Reset teleport flag at the end of the timer
 **********************************************************************************************************/
void UEsLyraCharacterMovementComponent::OnTeleportCooldownFinished()
{
	Safe_bWantsToTeleport = true;
}

#pragma endregion

#pragma region WallRun

/**
 *  Overwrite CanAttemptJump to read Jump press in air to WallJump or LateJump
 ****************************************************************************************/
bool UEsLyraCharacterMovementComponent::CanAttemptJump() const
{
	Safe_bWantsToWallRun = true;
	Proxy_bWantsToWallRun = true;
	return Super::CanAttemptJump() || CanWallJump() || bCanLateJump;
}

/**
 *  Overwrite DoJump excluding the wallJump and including LateJump
 ****************************************************************************************/
bool UEsLyraCharacterMovementComponent::DoJump(bool bReplayingMoves)
{	
	if(CanWallJump())
		return false;
	
	if (Super::DoJump(bReplayingMoves))
	{
		bCanLateJump = false;
		return true;
	}
	
	return false;
}

/**
 *  Called on Jump Released, activates WallJump if in WallRun
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::SetJumpEnd()
{	
	Safe_bWantsToWallRun = false;	

	//Wall Jump
	if(CanWallJump() && WallHit.bBlockingHit)
	{			
		SetMovementMode(MOVE_Falling);		
		Velocity = (CharacterOwner->GetActorForwardVector() + WallHit.Normal + FVector::UpVector * 2) * WallJumpOffForce;
#ifdef ENABLE_DEBUG_LINES
		DrawDebugLine(GetWorld(), Start, Start + Velocity, FColor::Silver, true, 1, 0, 4);
#endif
	}
}

/**
 *  Returns angle between OnGoing direction and Player looking direction
 ****************************************************************************************/
float UEsLyraCharacterMovementComponent::GetLookingAtAngle() const
{
	return FMath::RadiansToDegrees(acosf(FVector::DotProduct(Velocity.GetSafeNormal(), CharacterOwner->GetActorForwardVector())));
}

/**
 *  If JumpKey is pressed, search for a wall-runnable wall
 ****************************************************************************************/
bool UEsLyraCharacterMovementComponent::TryWallRun()
{	
	if(!Safe_bWantsToWallRun)
		return false;
	
	if (!IsFalling())
		return false;

	if(CanLateJump())
		return false;

	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector LeftEnd = Start - UpdatedComponent->GetRightVector() * CapsuleRScaled();
	FVector RightEnd = Start + UpdatedComponent->GetRightVector() * CapsuleRScaled();

	FCollisionQueryParams Params = ESCharacterOwner->GetIgnoreCharacterParams();	
	
	FHitResult FloorHit;
	// Check Player Height
	if (GetWorld()->LineTraceSingleByProfile(FloorHit, Start, Start + FVector::DownVector * (CapsuleHH() + MinWallRunHeight), "BlockAll", Params))
	{		
		return false;
	}
	
	// Left Cast
	GetWorld()->LineTraceSingleByProfile(WallHit, Start, LeftEnd, "BlockAll", Params);

	if (WallHit.IsValidBlockingHit() && (Velocity | WallHit.Normal) < 30)
	{
		Safe_bWallRunIsRight = false;
	}
	// Right Cast
	else
	{		
		GetWorld()->LineTraceSingleByProfile(WallHit, Start, RightEnd, "BlockAll", Params);
	
		if (WallHit.IsValidBlockingHit() && (Velocity | WallHit.Normal) < 30)
		{
			Safe_bWallRunIsRight = true;
		}
		else
		{	
			return false;
		}
	}

	SetMovementMode(MOVE_Custom, CMOVE_WallRun);
	WallRunDuration = WallRunMaxDuration;
	bWallRunForward = FVector::DotProduct(CharacterOwner->GetActorForwardVector(), Velocity.GetSafeNormal()) > 0;	
	
	return true;
}

/**
 *  CustomPhys, allows the player to WallRun and LateJump
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::PhysWallRun(float deltaTime, int32 Iterations)
{	
	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}
	if (!CharacterOwner || (!CharacterOwner->Controller && !bRunPhysicsWithNoController && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() && (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)))
	{
		Acceleration = FVector::ZeroVector;
		Velocity = FVector::ZeroVector;
		return;
	}
	
	bJustTeleported = false;
	float remainingTime = deltaTime;
	WallRunDuration -= deltaTime;
	
	// Perform the move	
	while ((remainingTime >= MIN_TICK_TIME) && (Iterations < MaxSimulationIterations) && CharacterOwner && (CharacterOwner->Controller || bRunPhysicsWithNoController || (CharacterOwner->GetLocalRole() == ROLE_SimulatedProxy)) )
	{
		Iterations++;
		bJustTeleported = false;
		const float timeTick = GetSimulationTimeStep(remainingTime, Iterations);
		remainingTime -= timeTick;
		const FVector OldLocation = UpdatedComponent->GetComponentLocation();		
		FVector Start = UpdatedComponent->GetComponentLocation();

		//Build Vector
		const FVector SideVector = FVector::CrossProduct(Velocity.GetSafeNormal(), FVector::DownVector) *
			((Safe_bWallRunIsRight) ? 1.f : -1.f) *
				((bWallRunForward) ? 1.f : -1.f);

		FCollisionQueryParams Params = ESCharacterOwner->GetIgnoreCharacterParams();		

		FVector VWallCheck = SideVector + Velocity.GetSafeNormal();
		VWallCheck *= CapsuleRScaled();

		// Check wall on forward and if not, on lateral
		GetWorld()->LineTraceSingleByProfile(WallHit, Start, Start + VWallCheck,  "BlockAll", Params);

		if(!WallHit.IsValidBlockingHit())
		{			
			VWallCheck = SideVector;
			VWallCheck *= CapsuleRScaled();
			GetWorld()->LineTraceSingleByProfile(WallHit, Start, Start + VWallCheck,  "BlockAll", Params);			
		}	

		// Clamp Acceleration
		Acceleration = FVector::VectorPlaneProject(Acceleration, WallHit.Normal);
		Acceleration.Z = 0.f;
		
		// Apply acceleration
		CalcVelocity(timeTick, 0.f, false, GetMaxBrakingDeceleration());
		Velocity = FVector::VectorPlaneProject(Velocity, WallHit.Normal);

		// Apply wall tangential velocity
		FVector Tangent = FVector::CrossProduct(WallHit.Normal, FVector::UpVector);			
		if (FVector::DotProduct(Tangent, Velocity) < 0)
		{
			Tangent *= -1.f;
		}
		Velocity += Tangent * WallRunSpeedFactor;
		
#ifdef ENABLE_DEBUG_LINES
		DrawDebugLine(GetWorld(), Start, Start + SideVector  * 100.f, FColor::Blue, true, .5f, 0, 2.f);		
		DrawDebugLine(GetWorld(), Start, Start + VWallCheck, FColor::Red, true, .5f, 0, 3.f);
		DrawDebugLine(GetWorld(), Start, Start + FVector::DownVector * (CapsuleHH() + MinWallRunHeight), FColor::Green);
		DrawDebugLine(GetWorld(), Start, Start + Velocity.GetSafeNormal() * 100.f, FColor::Black, true, .5f, 0, 2.f);
#endif
		
		// Compute move parameters
		const FVector Delta = timeTick * Velocity; // dx = v * dt		
		if ( Delta.IsNearlyZero() )
		{
			remainingTime = 0.f;
		}
		else
		{
			FHitResult Hit;
			SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), false, Hit);			
			FVector WallAttractionDelta = -WallHit.Normal * WallAttractionForce * timeTick;
			SafeMoveUpdatedComponent(WallAttractionDelta, UpdatedComponent->GetComponentQuat(), true, Hit);
		}

		//LateJump
		if (!WallHit.IsValidBlockingHit() ||  WallRunDuration < 0.f)
		{			
			SetMovementMode(MOVE_Falling);
			StartNewPhysics(remainingTime, Iterations);
			Safe_bWantsToWallRun = false;
			
			GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_LateJumpCooldown,
			this,
			&UEsLyraCharacterMovementComponent::OnLateJumpFinished,
			LateJumpDuration);
			bCanLateJump = true;
		
			return;
		}
		
		if (UpdatedComponent->GetComponentLocation() == OldLocation)
		{
			remainingTime = 0.f;
			break;
		}
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / timeTick; // v = dx / dt		
	}
}

/**
 *  Reset the LateJump timer
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::OnLateJumpFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LateJumpCooldown);
	bCanLateJump = false;
}

#pragma endregion 


#pragma region Interface

/**
 *  Returns the CustomMovementMode
 ****************************************************************************************/
bool UEsLyraCharacterMovementComponent::IsCustomMovementMode(const ECustomMovementMode InCustomMovementMode) const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == InCustomMovementMode;
}

/**
 *  Starts the teleportation. Called by Teleport GA
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::TeleportPressed()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if((CurrentTime < TeleportCooldownDuration) || (CurrentTime - TeleportStartTime >= TeleportCooldownDuration))
	{
		Safe_bWantsToTeleport = true;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_TeleportCooldown,
			this,
			&UEsLyraCharacterMovementComponent::OnTeleportCooldownFinished,
			TeleportCooldownDuration - (CurrentTime - TeleportStartTime));
	}
}

#pragma endregion

#pragma region Replication

/**
 *  Returns the properties used for network replication
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UEsLyraCharacterMovementComponent, Proxy_bWantsToWallRun, COND_SkipOwner);
}

#pragma endregion

#pragma region GettersSetters

/**
 *  OnRep notify for simulated proxy
 ****************************************************************************************/
void UEsLyraCharacterMovementComponent::OnRep_WallRun()
{
	Safe_bWantsToWallRun = Proxy_bWantsToWallRun;
}

/**
 *  Returns Scaled Capsule Component radius of the character
 ****************************************************************************************/
float UEsLyraCharacterMovementComponent::CapsuleR() const
{
	return CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
}

/**
 *  Returns Scaled Capsule Component radius of the character, scaled by a factor
 ****************************************************************************************/
float UEsLyraCharacterMovementComponent::CapsuleRScaled() const
{
	return CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius() * CapsuleScaleFactor;
}

/**
 *  Returns Scaled Capsule Component half height of the character
 ****************************************************************************************/
float UEsLyraCharacterMovementComponent::CapsuleHH() const
{
	return CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

#pragma endregion


#pragma region SavedMove

FSavedMove_Es::FSavedMove_Es()
{
	Saved_bWantsToTeleport = 0;
	Saved_bWallRunIsRight = 0;
	Saved_bWantsToWallRun = 0;
}

void FSavedMove_Es::Clear()
{
	Super::Clear();

	Saved_bWantsToTeleport = 0;
	Saved_bWallRunIsRight = 0;
	Saved_bWantsToWallRun = 0;
}

/**
 *  Called to set up this saved move to make a predictive correction.
 ****************************************************************************************/
void FSavedMove_Es::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const UEsLyraCharacterMovementComponent* CharacterMovement = Cast<UEsLyraCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToWallRun = CharacterMovement->Safe_bWantsToWallRun;
	Saved_bWantsToTeleport = CharacterMovement->Safe_bWantsToTeleport;
	Saved_bWallRunIsRight = CharacterMovement->Safe_bWallRunIsRight;
}

/**
 *  Returns true if this move can be combined with NewMove for replication without changing any behavior
 ****************************************************************************************/
bool FSavedMove_Es::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	const FSavedMove_Es* NewEsMove = static_cast<FSavedMove_Es*>(NewMove.Get());

	if(Saved_bWantsToTeleport != NewEsMove->Saved_bWantsToTeleport)
	{
		return false;
	}

	if(Saved_bWantsToWallRun != NewEsMove->Saved_bWantsToWallRun)
	{
		return false;
	}

	if(Saved_bWallRunIsRight != NewEsMove->Saved_bWallRunIsRight)
	{
		return false;
	}
		
	return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

/**
 *  Called before ClientUpdatePosition uses this SavedMove to make a predictive correction
 ****************************************************************************************/
void FSavedMove_Es::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	UEsLyraCharacterMovementComponent* CharacterMovement = Cast<UEsLyraCharacterMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToTeleport = Saved_bWantsToTeleport;
	
	CharacterMovement->Safe_bWantsToWallRun = Saved_bWantsToWallRun;
	CharacterMovement->Safe_bWallRunIsRight = Saved_bWallRunIsRight;
}

/**
 *  Returns a byte containing encoded special movement information, plus custom ones
 ****************************************************************************************/
uint8 FSavedMove_Es::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if(Saved_bWantsToTeleport)
	{
		Result |= FLAG_Teleport;
	}

	if(Saved_bWantsToWallRun)
	{
		Result |= FLAG_WallRun;
	}
	
	return Result;
}

#pragma endregion 

#pragma region Client Network Prediction Data

FNetworkPredictionData_Client_Es::FNetworkPredictionData_Client_Es(const UCharacterMovementComponent& ClientMovement)
: Super(ClientMovement)
{
}

FSavedMovePtr FNetworkPredictionData_Client_Es::AllocateNewMove()
{	
	return FSavedMovePtr(new FSavedMove_Es());
}

#pragma endregion
