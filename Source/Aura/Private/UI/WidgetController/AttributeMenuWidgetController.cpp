// Tutorial Project 


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	// Get the AttributeSet and find the value of an attribute.
	// We have an AttributeSet variable in the Base Widget Controller
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	//Check the AttributeInfo DataAsset was correctly set to the Controller on BP
	check(AttributeInfo);

	//Loop through the TagsToAttributes Map and broadcast each element
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	// We have an AttributeSet variable in the Base Widget Controller
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	//Check the AttributeInfo DataAsset was correctly set to the Controller on BP
	check(AttributeInfo);

	//Loop through the TagsToAttributes Map and broadcast for each Attribute's change
	for (auto& Pair : AS->TagsToAttributes)
	{
		//Whenever an Attribute changes, the Lambda will be called:
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	//Get the Attribute corresponding to the Tag and broadcast its changes:
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet); //Fill the Attribute Value
	//Broadcast
	AttributeInfoDelegate.Broadcast(Info);
}


