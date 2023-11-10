// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraCharacterMovementComponent.h"
#include "EsLyraCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UEsLyraCharacterMovementComponent : public ULyraCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UEsLyraCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	
	// Teleport
	UPROPERTY(EditDefaultsOnly)
	float TeleportImpulse = 4000.f;

	UPROPERTY(EditDefaultsOnly)
	float TeleportCooldownDuration = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float AuthTeleportCooldownDuration = 4.f;

	/*
	 *  Flags (Transient)
	 */
	
	bool Safe_bWantsToTeleport;

	float TeleportStartTime;
	FTimerHandle TimerHandle_TeleportCooldown;

	/*
	 *  Replication
	 */
	
	/*
	 *  Delegates
	 */
	
protected:
	// Movement Pipeline
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

private:
	/*
	 *  Teleport
	 */
	
	void PerformTeleport();
	void OnTeleportCooldownFinished();

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

	UFUNCTION(BlueprintCallable)
	bool CanTeleport() const;

	UFUNCTION(BlueprintCallable)
	void TeleportPressed();

	UFUNCTION(BlueprintCallable)
	void TeleportReleased();

/*
 *  Proxy Replication
 */
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
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

