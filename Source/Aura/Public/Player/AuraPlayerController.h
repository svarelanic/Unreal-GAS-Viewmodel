// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

//Forward declaring the IEnemyInterface
class IEnemyInterface;
//Forward declaring the Input Mapping Context type
class UInputMappingContext;
//Forward delcaring the Input Action type
class UInputAction;
//Forward delcaring the FInputActionValue type
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

private: 
	//Variable thar will hold the Input Mapping Context created in the Editor
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	//Variable thar will hold the Input Action for moving
	//Link the MoveAction to the Move function
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	//Callback function to move the Player
	//FInputActionValue is used to bind Move to an Input Action that provides Data
	void Move(const FInputActionValue& InputActionValue);

	//Getting the Actor that the Player Controller by hovering Over with the Mouse. 
	//From this, we'll check if it implements IEnemyInterface and, if it does, the Actor
	//does the function to highlight the Enemy:
	void CursorTrace();

	//We'll get two IEnemyInterface pointers where we'll save the Hit from this frame 
	//and the Hit from last Frame
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

protected:
	virtual void BeginPlay() override;

	//Linking our Input Mapping actions to a Callback function:
	virtual void SetupInputComponent() override;
};
