// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:

	//Getter function for the OverlayWidgetController-> create the OverlayWidgetController
	//if it hasn't been created yet, and if it has, return that OverlayWidgetController:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	//Getter function for the AttributeMenuWidgetController-> create the AttributeMenuWidgetController
	//if it hasn't been created yet, and if it has, return that OverlayWidgetController:
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	//Function to create the OverlayWidgetController in, since we can pass in the WCParams variables:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	//This function will be called in InitAbilityActorInfo function of AuraCharacter.cpp
	//where all PC, PS, ASC, and AS are all set
	
private:
	//To store the Overlay Widget itself we want to display On-Screen:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	//To store the UClass of the Widget we want to create.
	//This one we'll set from the BP_AuraHUD and will determine the class of the Widget we
	//want to create:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	

	//Variable in which the OverlayWidgetController will be stored into by the Getter if the Controller has already
	//been created
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	//To store the UClass of the WidgetController we want to create.
	//This one we'll set from the BP_AuraHUD and will determine the class of the WidgetController:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	//Variable in which the OverlayWidgetController will be stored into by the Getter if the Controller has already
	//been created
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	//To store the UClass of the WidgetController we want to create.
	//This one we'll set from the BP_AuraHUD and will determine the class of the WidgetController:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
