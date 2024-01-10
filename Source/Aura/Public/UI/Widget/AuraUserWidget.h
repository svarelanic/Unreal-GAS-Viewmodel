// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Variable to store the Widget Controller
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	//To associate the Controller with WidgetControllerSet:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:
	//To initialize Visuals, we'll use a BeginPlay like function that starts once
	//the Controller is set
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	

	
};
