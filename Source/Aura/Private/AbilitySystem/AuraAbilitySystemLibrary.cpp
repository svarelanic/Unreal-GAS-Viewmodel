// Tutorial Project 


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	//Get the WidgetController and return it to the caller:
	
	//Get the PlayerController associated with the instance
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		//Access the HUD from the Player Controller
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			//For getting the WidgetController, we'll need the WidgetController Params (PC, PS, ASC, AS)
			//Get the PlayerState from the PlayerController, to get function for accessing AbilitySystemComponent and AttributeSet
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			//Make the WidgetControllerParams struct defined in AuraWidgetController.h:
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			
			//Get the WidgetController from the HUD passing in the WidgetControllerParams and return it
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr; //we shouldn't make it to the end but, if we do, return a nullptr
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		//Access the HUD from the Player Controller
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			//For getting the WidgetController, we'll need the WidgetController Params (PC, PS, ASC, AS)
			//Get the PlayerState from the PlayerController, to get function for accessing AbilitySystemComponent and AttributeSet
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			//Make the WidgetControllerParams struct defined in AuraWidgetController.h:
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			
			//Get the WidgetController from the HUD passing in the WidgetControllerParams and return it
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr; //we shouldn't make it to the end but, if we do, return a nullptr
}
