// Tutorial Project 


#include "UI/HUD/AuraHUD.h"

#include "Ui/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	//If the OverlayWidgetController does not exist, we'll create one:
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		//Setting the WidgetController Parameters to the newly created object
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//Binding the callback functions to the Widget's delegates, so that Data is
		//broadcasted correctly to the Widgets when attributes/dependencies change
		OverlayWidgetController->BindCallbacksToDependencies();
		
		//return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	//If the AttributeMenuWidgetController does not exist, we'll create one:
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		//Setting the WidgetController Parameters to the newly created object
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		//Binding the callback functions to the Widget's delegates, so that Data is
		//broadcasted correctly to the Widgets when attributes/dependencies change
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//Checking if OverlayWidgetClass and OverlayWidgetControllerClass where correctly set in the BP_AuraHUD
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass unitilized, initialize it in BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass unitilized, initialize it in BP_AuraHUD"));
	
	//Create the OverlayWidget 
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	//Create the WidgetController calling GetOverlayWidgetController and passing in the struct for the Params
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS); //initialize the struct using the parameters
																	       //from InitOverlay
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	//Tie the OverlayWidget and the OverlayWidgetController together:
	OverlayWidget->SetWidgetController(WidgetController);

	//Calling BroadcastInitialValues to broadcast from the OverlayWidgetController
	WidgetController->BroadcastInitialValues();
	
	//Adding the Widget of OverlayWidgetClass to the Viewport
	Widget->AddToViewport(); 
}



