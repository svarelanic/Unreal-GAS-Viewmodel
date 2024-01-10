// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"


class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//For the OverlayWidgetController
	//Needs a WorldContextObject since it is a static function -> Needs a reference to trace up to objects that exist in the world
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController") //BlueprintPure because it does not need an execution pin (it will only perform an operation and return a result)
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	//For the AttributeMenuWidgetController
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController") 
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
