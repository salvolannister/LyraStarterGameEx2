// Fill out your copyright notice in the Description page of Project Settings.


#include <Character/JetpackComponent.h>

#include "LyraLogChannels.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraCombatSet.h"

UJetpackComponent::UJetpackComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	CombatSet = nullptr;
}

void UJetpackComponent::InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraJetpackComponent: Mana component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraJetpackComponent: Cannot initialize Mana component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	CombatSet = AbilitySystemComponent->GetSet<ULyraCombatSet>();
	if (!CombatSet)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraJetpackComponent: Cannot initialize Mana component for owner [%s] with NULL Mana set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ULyraCombatSet::GetJetpackResourceAttribute()).AddUObject(this, &ThisClass::HandleJetpackResourceChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ULyraCombatSet::GetMaxJetpackResourceAttribute()).AddUObject(this, &ThisClass::HandleMaxJetpackResourceChanged);
}

void UJetpackComponent::UninitializeFromAbilitySystem()
{
	CombatSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float UJetpackComponent::GetJetpackResource() const
{
	return (CombatSet ? CombatSet->GetJetpackResource() : 0.0f);
}

float UJetpackComponent::GetMaxJetpackResource() const
{
	return (CombatSet ? CombatSet->GetMaxJetpackResource() : 0.0f);
}

float UJetpackComponent::GetJetpackResourceNormalized() const
{
	if (CombatSet)
	{
		const float Mana = CombatSet->GetJetpackResource();
		const float MaxMana = CombatSet->GetMaxJetpackResource();

		return ((MaxMana > 0.0f) ? (Mana / MaxMana) : 0.0f);
	}

	return 0.0f;
}

void UJetpackComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();
	
	Super::OnUnregister();
}

void UJetpackComponent::HandleJetpackResourceChanged(const FOnAttributeChangeData& ChangeData)
{
	OnJetpackResourceChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue);
}

void UJetpackComponent::HandleMaxJetpackResourceChanged(const FOnAttributeChangeData& ChangeData)
{
	OnMaxJetpackResourceChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue);
}