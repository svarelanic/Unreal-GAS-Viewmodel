// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


//Struct to store all the information associated with a given attribute, so once it changes we can broadcast this struct object up to the WBPs to update themselves
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY();

	//gameplay tag to identify which attribute this info is for
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag(); //Initialize it with an empty tag

	//Information to pass up to widgets:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();//Using FText since we'll set text for Widgets

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly) //not exposable to the Data Asset using EditDefaultsOnly, since this is not where this value is set
	float AttributeValue = 0.f;
};

/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset //We can fill it in with info on BP
{
	GENERATED_BODY()
	
public:
	//Pass in a Tag and receive an AttributeInfo struct
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const; //if bool is true, so if we try to find an non existent AttributeInfo struct in the Array, we'll log an error
	
	//To fill with Structs. Will fill it in on the BP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
};
