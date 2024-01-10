// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

//STRUCT to define the Row Structure to a Data Table to broadcast information into the
//HUD from GameplayEffects' Gameplay Tags:
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY();

	//Tag to use for messages to display on the HUD
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); //Initialized to an Empty Gameplay Tag

	//Message to display
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	//Widget Class we can show on the Screen for each GameplayTag received from GEs
	//We'll set it from BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	//Optional Image to show on screen
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};


//Delegate to Broadcast Initial Values into Widgets
//We'll use Dynamic Multicast Delegate. It is Dynamic Multicast because we want
//to assign events to ot in the Widget BP, and Multicast because multiple Widget BPs
//may want to bind to this Delegate, so that it can update


//Delegate type that will trigger when an attribute changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, //Delegate's type
	float, //Type of parameter it will send
	NewValue); //parameter it will send


//Delegate for all Messages from Message Tags, since we can broadcast the DataTable Row
//This Delegate will be used to broadcast the Message by binding a Widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	//overriding function to set Initial Values
	virtual void BroadcastInitialValues() override; //Will be called AFTER
											       //the WidgetController
											       //is set to the Overlay Widget
	//overriding to bind Callback functions to the on Attribute Change Delegate
	virtual void BindCallbacksToDependencies() override; //Called when the Widget
														//is first constructed under AuraHUD

	//Member Variables for the Multicast Delegates to Broadcast Initial Values
	//These are the Delegates themselves. We can BIND to them in BP
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	//Member variable of Message Delegate Type:
	UPROPERTY(BlueprintAssignable, Category="GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:
	//Data Table variable to look up ingo if we've received a Message Tag from a GE
	//we'll assign it the DT_MessageWidgetDataTable we created using the FUIWidget
	//STRUCT Row Structure in BP:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	

	//Take a Data Table and a Gameplay Tag, and return any type of Row type,
	//we'll use a Template for it:
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
};

//This remains in the .h file since it is a template T type
template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	//look for row by Name, since row name and tag name are the same
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}