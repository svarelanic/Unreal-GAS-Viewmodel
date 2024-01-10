// Tutorial Project 


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	//Loop through each TSubclassOF in the Array and grant abilities
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		//We must create an Ability Spec from each of these classes
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		//Use function from the ASC that takes in the AbilitySpec just created
		/* GiveAbility(AbilitySpec); */ //Can accept a const ability spec
		//Function to both give and activate ability
		GiveAbilityAndActivateOnce(AbilitySpec); //Cannot accept a const ability spec
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//Showing the GameplayEffect in the HUD:

	// Our ASC must have a Delegate that broadcasts a Gameplay Tag to the WidgetController
	FGameplayTagContainer TagContainer; //Our Tags will be stored here
	EffectSpec.GetAllAssetTags(TagContainer);

	//Broadcasting the TagContainer using the custom EffectAssetTags Delegate:
	EffectAssetTags.Broadcast(TagContainer);
	
}

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//Bind the EffectApplied callback function to the OnGameplayEffectAppliedDelegateToSelf
	//delegate, which is called everytime a GameplayEffect is applied to self
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

}
