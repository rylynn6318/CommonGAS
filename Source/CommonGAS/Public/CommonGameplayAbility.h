// Copyright 2026 rylynn6318. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CommonGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class COMMONGAS_API UCommonGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	// Control Cooldown via SetByCaller
	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	// ~SetByCaller
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	APlayerController* GetPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	AController* GetControllerFromActorInfo() const;

protected:
	// 쿨다운 태그, 태그 별로 한개의 쿨타임만 적용됨.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Cooldown", meta = (Categories = "SetByCaller"))
	FGameplayTagContainer CooldownTags;

	// 쿨다운 지속시간
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Cooldown")
	FScalableFloat CooldownDuration;

private:
	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags;
};
