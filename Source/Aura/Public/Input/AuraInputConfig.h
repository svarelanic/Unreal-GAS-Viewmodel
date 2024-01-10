// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

//Struct to link-up Input Actions with Gameplay Tags for assigning input to Gameplay Abilities
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	//Will contain an InputAction
	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	//And will contain a GameplayTag
	//This Tags can be added to our project natively in AuraGameplayTags
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

	//Now the DataAsset can contain an Array of these that we can set on the DataAsset BP
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	//To hold FAuraInputAction (an InputAction associated to a GameplayTag) types 
	//Will fill in BP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;

	//With a Reference to this DataAsset, we can use a Function to look up in this Array any InputAction with a specific type
	//Returns only the UInputAction associated with the Tag, not the whole Struct.
	//The InputAction is what we use, the Tag helps us find it
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
};
