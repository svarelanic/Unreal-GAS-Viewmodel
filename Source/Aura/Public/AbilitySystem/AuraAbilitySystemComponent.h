// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

//Declaring Delegate to broadcast GameplayTags to WidgetController:
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//Function called when InitAbilityActorInfo() has been called in each Character
	void AbilityActorInfoSet();

	//Delegate to broadcast. Must Bind it to the custom WidgetController (inside
	//BindCallbacksToDependencies function) in order t broadcast to the HUD correctly
	FEffectAssetTags EffectAssetTags;

	//To give GameplayAbilities to an Array of Abilities present on the CharacterBase class
	//It must take in the TArray of GameplayAbilities TSubclassOf
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
protected:
	//Callback function bindable to OnGameplayEffectAppliedDelegateToSelf delegate from
	//AbilitySystemComponent.h (signature is from here), called on server
	//when GE is applied to self
	//Bind it to the Delegate as soon as we Initialized the AbilityActorInfo
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
