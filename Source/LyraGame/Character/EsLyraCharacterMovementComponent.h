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
 * 
 */
UCLASS()
class LYRAGAME_API UEsLyraCharacterMovementComponent : public ULyraCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UEsLyraCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeComponent() override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	
	virtual bool CanAttemptJump() const override;
	virtual bool DoJump(bool bReplayingMoves) override;
	

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
	float WallAttractionForce = 200.f;
	
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
	bool Safe_bWallRunIsRight;
	bool Safe_bWantsToWallJump;

	

	float TeleportStartTime;
	FTimerHandle TimerHandle_TeleportCooldown;

	FTimerHandle TimerHandle_LateJumpCooldown;
	/*
	 *  Replication
	 */
	
	/*
	 *  Delegates
	 */
	
protected:
	// Movement Pipeline
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	//virtual void UpdateCharacterStateAfterMovement(float DeltaSeconds) override;
	//virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	
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

	float WallRunDuration;
	bool bWallRunForward;
	bool bCanLateJump;

protected:
	/*
	 *  Network
	 */
	virtual void OnClientCorrectionReceived(FNetworkPredictionData_Client_Character& ClientData, float TimeStamp, FVector NewLocation, FVector NewVelocity, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode) override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

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
	void TeleportReleased();
		
	UFUNCTION(BlueprintCallable)
	void SetJumpEnd();
	
	UFUNCTION(BlueprintPure)
	bool IsWallRunning() const { return IsCustomMovementMode(CMOVE_WallRun); }
	
	UFUNCTION(BlueprintPure)
	bool WallRunningIsRight() const { return Safe_bWallRunIsRight; }

	bool CanWallJump() const {return IsWallRunning(); };

	bool CanLateJump() const { return bCanLateJump; };

	/*
	 *  Proxy Replication
	 */
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	 *  Getter/Setters
	 */

	float CapsuleR() const;
	float CapsuleRScaled() const;
	float CapsuleHH() const;
	
private:
	
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
		FLAG_Custom_1		= 0x20,
		FLAG_Custom_2		= 0x40,
		FLAG_Custom_3		= 0x80,
	};
	
	/*
	 *  Flags
	 */
	
	uint8 Saved_bWantsToTeleport:1;
	uint8 Saved_bWallRunIsRight:1;
	
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
};


class FNetworkPredictionData_Client_Es : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;
	
	FNetworkPredictionData_Client_Es(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};

