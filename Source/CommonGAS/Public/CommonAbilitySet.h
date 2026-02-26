// Copyright 2026 rylynn6318. All rights reserved.

#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "AttributeSet.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"

#include "CommonAbilitySet.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class UObject;

/**
 * Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct COMMONGAS_API FCommonAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:
	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct COMMONGAS_API FCommonAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct COMMONGAS_API FCommonAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	// Attribute set to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;
};

/**
 * Handles to abilities, effects, and attribute sets granted by the ability set.
 */
USTRUCT(BlueprintType)
struct COMMONGAS_API FCommonAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent);

protected:
	// Handles to granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to granted attribute sets.
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

/**
 * Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS(BlueprintType, Const)
class COMMONGAS_API UCommonAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UCommonAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Grants this ability set to the specified ability system component.
	// Returned handles can be used later to take away anything that was granted.
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent, FCommonAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", Meta = (TitleProperty = Ability))
	TArray<FCommonAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", Meta = (TitleProperty = GameplayEffect))
	TArray<FCommonAbilitySet_GameplayEffect> GrantedGameplayEffects;

	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", Meta = (TitleProperty = AttributeSet))
	TArray<FCommonAbilitySet_AttributeSet> GrantedAttributes;
};
