// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo; //Forward declaring the struct to use on the Delegate
//Delegate capable of sending our FAuraAttributeInfo struct up to the Widgets
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	
	//To broadcast Initial Values into the compatible UserWidgets
	virtual void BroadcastInitialValues() override; //we'll use it in child classes

	//To bind Callbacks to Dependencies in WidgetControllers:
	virtual void BindCallbacksToDependencies() override; //we'll use it in child classes

	//Delegate member variable
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	//DataAsset member variable used for broadcasting the information up to the widgets
	//we'll set it on BP and use it to look up our AttributeInfo based on the GameplayTag
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	//To broadcast Attribute info, both init values and listening to changes
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
