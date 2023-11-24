// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraCharacterMovementComponent.h"
#include "EsLyraCharacterMovementComponent.generated.h"


class ALyraCharacter;

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None			UMETA(Hidden),
	CMOVE_WallRun		UMETA(DisplayName = "Wall Run"),
	CMOVE_MAX			UMETA(Hidden),
};


/**
 *  Custom character movement component class for the Lyra game.
 *  This class extends ULyraCharacterMovementComponent to add new movement abilities
 */
UCLASS()
class LYRAGAME_API UEsLyraCharacterMovementComponent : public ULyraCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UEsLyraCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	/** <UCharacterMovementComponent> */
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	/** </UCharacterMovementComponent> */
	
	/** <ULyraCharacterMovementComponent> */
	virtual void InitializeComponent() override;
	virtual bool CanAttemptJump() const override;
	virtual bool DoJump(bool bReplayingMoves) override;
	/** </ULyraCharacterMovementComponent> */

	/*
	 *  Parameters
	 */

	UPROPERTY(Transient) 
	TObjectPtr<ALyraCharacter> ESCharacterOwner;
	
	// Teleport
	UPROPERTY(EditDefaultsOnly)
	float TeleportImpulse = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float TeleportCooldownDuration = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float AuthTeleportCooldownDuration = 4.f;

	// Wall Run
	UPROPERTY(EditDefaultsOnly)
	float WallRunMaxDuration = 3.f;

	UPROPERTY(EditDefaultsOnly) 
	float WallRunSpeedFactor= 50.f;
	
	UPROPERTY(EditDefaultsOnly) 
	float WallAttractionForce = 300.f;
	
	UPROPERTY(EditDefaultsOnly) 
	float MinWallRunHeight = 50.f;
	
	UPROPERTY(EditDefaultsOnly) 
	float WallJumpOffForce = 300.f;

	UPROPERTY(EditDefaultsOnly)
	float CapsuleScaleFactor = 3.f;

	UPROPERTY(EditDefaultsOnly)
	float LateJumpDuration = 1.f;

	/*
	 *  Flags (Transient)
	 */
	
	bool Safe_bWantsToTeleport;
	mutable bool Safe_bWantsToWallRun;

	float TeleportStartTime;
	FTimerHandle TimerHandle_TeleportCooldown;

	FTimerHandle TimerHandle_LateJumpCooldown;
	
	/*
	 *  Replication
	 */

	UPROPERTY(Replicated)
	float WallRunDuration;
	
	/*
	 *  Delegates
	 */
	
protected:
	// Movement Pipeline
	/** <UCharacterMovementComponent> */
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	/** </UCharacterMovementComponent> */
	
private:
	/*
	 *  Teleport
	 */
	
	void PerformTeleport();
	void OnTeleportCooldownFinished();

	/*
	 *  WallRun
	 */

	bool TryWallRun();
	void PhysWallRun(float deltaTime, int32 Iterations);
	void OnLateJumpFinished();

	UPROPERTY(Replicated)
	bool bWallRunIsRight;
	
	UPROPERTY(Replicated)
	bool bWallRunForward;
	
	bool bCanLateJump;	
	FHitResult WallHit;

protected:
	/*
	 *  Network
	 */
	
	/** <UCharacterMovementComponent> */
	virtual void OnClientCorrectionReceived(FNetworkPredictionData_Client_Character& ClientData, float TimeStamp, FVector NewLocation, FVector NewVelocity, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode) override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	/** </UCharacterMovementComponent> */
	
public:
	/*
	 *  Interface
	 */

	UFUNCTION(BlueprintPure)
	bool IsCustomMovementMode(const ECustomMovementMode InCustomMovementMode) const;

	UFUNCTION(BlueprintCallable)
	bool CanTeleport() const;

	UFUNCTION(BlueprintCallable)
	void TeleportPressed();
		
	UFUNCTION(BlueprintCallable)
	void SetJumpEnd();
	
	UFUNCTION(BlueprintPure) FORCEINLINE
	bool IsWallRunning() const { return IsCustomMovementMode(CMOVE_WallRun); }
	
	UFUNCTION(BlueprintPure) FORCEINLINE
	bool WallRunningIsRight() const { return bWallRunIsRight; }

	UFUNCTION(BlueprintPure)
	float GetLookingAtAngle() const;
	
	UFUNCTION(BlueprintPure) FORCEINLINE
	bool GetIsGoingForward() const {return bWallRunForward; };

	FORCEINLINE bool CanWallJump() const {return IsWallRunning(); };

	FORCEINLINE bool CanLateJump() const { return bCanLateJump; };

	/*
	 *  Proxy Replication
	 */

	/** </UActorComponent> */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/** </UActorComponent> */

private:
	
	/*
	 *  Getter/Setters
	 */

	float CapsuleR() const;
	float CapsuleRScaled() const;
	float CapsuleHH() const;
	
};

/** FSavedMove_Character represents a saved move on the client that has been sent to the server and might need to be played back. */
class LYRAGAME_API FSavedMove_Es : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;

	FSavedMove_Es();
	
	// Bit masks used by GetCompressedFlags() to encode movement information.
	enum CompressedFlags
	{
		// Remaining bit masks are available for custom flags.
		FLAG_Teleport		= 0x10, // Teleport pressed
		FLAG_WallRun		= 0x20, // Wallrun pressed
		FLAG_Custom_2		= 0x40,
		FLAG_Custom_3		= 0x80,
	};
	
	/*
	 *  Flags
	 */
	
	uint8 Saved_bWantsToTeleport:1;

	uint8 Saved_bWantsToWallRun:1;

	/** <FSavedMove_Es> */
	
	/** Clear saved move properties, so it can be re-used. */
	virtual void Clear() override;

	/** Called to set up this saved move (when initially created) to make a predictive correction. */
	virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character & ClientData) override;	

	/** Returns true if this move can be combined with NewMove for replication without changing any behavior */
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;

	/** Called before ClientUpdatePosition uses this SavedMove to make a predictive correction	 */
	virtual void PrepMoveFor(ACharacter* C) override;

	/** Returns a byte containing encoded special movement information (jumping, crouching, etc.)	 */
	virtual uint8 GetCompressedFlags() const override;
	
	/** </FSavedMove_Es> */
};


class FNetworkPredictionData_Client_Es : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;
	
	FNetworkPredictionData_Client_Es(const UCharacterMovementComponent& ClientMovement);
	
	/** <FNetworkPredictionData_Client_Es> */
	virtual FSavedMovePtr AllocateNewMove() override;
	/** </FNetworkPredictionData_Client_Es> */
};

