// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

//Forward declaration for AS
class UAttributeSet;
//Forward declaration for ASC
class UAbilitySystemComponent;

//Struct to initialize the WidgetController's variables, which we'll then set on a
//WidgetController function. BlueprintType allows us to expose its members to BP
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {} //Empty Constructor 
	//Initialization Constructor with member initializer list
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS,
		UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC),
	AttributeSet(AS) {} 

	//Define the Variables to Initialize, must be initialize as nullptr to prevent compilation errors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	//To Set the Variables initialized in Struct:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	//To broadcast Initial Values into the compatible UserWidgets
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues(); //we'll use it in child classes

	//To bind Callbacks to Dependencies in WidgetControllers:
	virtual void BindCallbacksToDependencies(); //we'll use it in child classes
	
protected:
	//The WidgetController will access and broadcast Data, which will be accessed from
	//the following classes:
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet;
	
};
