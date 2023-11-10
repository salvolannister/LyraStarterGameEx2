// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EsLyraCharacterMovementComponent.h"
#include "GameFramework/Character.h"

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


#pragma region Teleport

UEsLyraCharacterMovementComponent::UEsLyraCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Safe_bWantsToTeleport = false;
	TeleportStartTime = 0.f;
}

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
	
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
}

bool UEsLyraCharacterMovementComponent::CanTeleport() const
{
	return IsWalking() || IsFalling();
}

void UEsLyraCharacterMovementComponent::PerformTeleport()
{
	//Use velocity if want to avoid sweep
	TeleportStartTime = GetWorld()->GetTimeSeconds();	
	
	const FVector ForwardVector = UpdatedComponent->GetForwardVector();
	FHitResult Hit;

	SafeMoveUpdatedComponent(ForwardVector * 1000.0f, UpdatedComponent->GetComponentRotation(), true, Hit, ETeleportType::None);

	SetMovementMode(MOVE_Falling);
}

void UEsLyraCharacterMovementComponent::OnTeleportCooldownFinished()
{
	Safe_bWantsToTeleport = true;
}

void UEsLyraCharacterMovementComponent::OnClientCorrectionReceived(FNetworkPredictionData_Client_Character& ClientData,
	float TimeStamp, FVector NewLocation, FVector NewVelocity, UPrimitiveComponent* NewBase, FName NewBaseBoneName,
	bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode)
{
	Super::OnClientCorrectionReceived(ClientData, TimeStamp, NewLocation, NewVelocity, NewBase, NewBaseBoneName,
	                                  bHasBase, bBaseRelativePosition,
	                                  ServerMovementMode);

	UE_LOG(LogTemp, Warning, TEXT("On Client Correction Received"));
}

void UEsLyraCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToTeleport = (Flags & FSavedMove_Es::FLAG_Teleport) != 0;
}

#pragma endregion

#pragma region Interface

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

void UEsLyraCharacterMovementComponent::TeleportReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_TeleportCooldown);
	Safe_bWantsToTeleport = false;
}

#pragma endregion

#pragma region Replication

void UEsLyraCharacterMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

#pragma endregion

#pragma region SavedMove

FSavedMove_Es::FSavedMove_Es()
{
	Saved_bWantsToTeleport = 0;
}

void FSavedMove_Es::Clear()
{
	Super::Clear();

	Saved_bWantsToTeleport = 0;
}

void FSavedMove_Es::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const UEsLyraCharacterMovementComponent* CharacterMovement = Cast<UEsLyraCharacterMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToTeleport = CharacterMovement->Safe_bWantsToTeleport;
}

bool FSavedMove_Es::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	const FSavedMove_Es* NewEsMove = static_cast<FSavedMove_Es*>(NewMove.Get());

	if(Saved_bWantsToTeleport != NewEsMove->Saved_bWantsToTeleport)
	{
		return false;
	}
		
	return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void FSavedMove_Es::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	UEsLyraCharacterMovementComponent* CharacterMovement = Cast<UEsLyraCharacterMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToTeleport = Saved_bWantsToTeleport;
}

uint8 FSavedMove_Es::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if(Saved_bWantsToTeleport)
	{
		Result |= FLAG_Teleport;
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
