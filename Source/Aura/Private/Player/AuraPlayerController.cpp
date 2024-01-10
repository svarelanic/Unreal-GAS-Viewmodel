// Tutorial Project 


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"



AAuraPlayerController::AAuraPlayerController()
{
	//Player Controller Replicates from Server to Client: 
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//Get the Actor the Player Controller is hovering over with the mouse every frame
	CursorTrace();

}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, //Collision Channel used, trace against visibility
							false, //do not trace complex, only trace against simple collisions
							CursorHit); //Will save the data in this HitResult variable 
	
	//If bBlockingHit is false, there was no Hit with any collision
	if (!CursorHit.bBlockingHit) return; 

	//Check if it the Hit Actor implements the IEnemyInterface and 
	//Definine the current actor being hovered over and the one hovered over last frame
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor()); //If cast succeeds, it implements the Interface
															//If it fails, it returns a null pointer, we can use it

	/*
		Scenarios that can Occur when hovering over Actors:
			A -> Last Actor is null && ThisActor is null
				- Do nothing
			B-> LastActor is null && ThisActor is valid
				- Highlight ThisActor
			C-> Last Actor is valid && This Actor is null
				- UnHihglight LastActor
			D-> Both Actors are valid, but LastActor != ThisActor
				- UnHighlight Last Actor and Hihglight ThisActor
			E-> Both Actors are valid, and are the same actor
				- Do nothing
	*/

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case B
			ThisActor->HighlightActor();
		}
		//else, Case A - both are null, do nothing
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			//Case C
			LastActor->UnHighlightActor();
		}
		else //Both actors are valid
		{
			if (LastActor != ThisActor)
			{
				//Case D - Actors are different, unhighlight the last one and hihglight the new one
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			//Else, Case E - both actors are the same, do nothing
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Adding the Input Mapping Context to the Character---------- 
	
	//Assert: terminates execution if AuraContext is not valid -> If it is not set in the Editor
	check(AuraContext);

	//We add IMC with AddMappingContext(), which is in the EnhancedInputLocalPlayerSubsystem class
	//We access the class with GetSubsystem(), check it, and call AddMappingContext() from it
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem)
	{
		//Add the IMC from the Subsystem:
		Subsystem->AddMappingContext(AuraContext, 0); // 0 is the priority, useful when there are multiple mappings active at once. 
	}

	//Some additional BeginPlay Settings---------- 

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;//Data structure to setup an Input Mode that allows UI to respond to Player or Controller Input
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); //Not lock mouse to viewport
	InputModeData.SetHideCursorDuringCapture(false); //Not hide the cursor when captured into Viewport
	//To set this Input Mode Settings: 
	SetInputMode(InputModeData);


}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Casting an InputComponent variable present in the PlayerController into an EnhancedInputComponent
	//CastChecked gives us an assert fail if cast fails
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	//EnhancedInputComponent has the BindAction() function that will let us bind 
	//the Move function the the MoveAction InputAction:
	EnhancedInputComponent->BindAction(MoveAction, //Action to bind
		ETriggerEvent::Triggered, //Type of event, in this case as long as we press the key we'll move
		this, //The player object
		&AAuraPlayerController::Move);//The callback function to bind to

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//Here we hadle the movement functionality:

	//Get the FInputActionValue so we can get the X and Y Data from it:
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	
	//Add movement to our controller pawn:
	//Get the Controller's rotation, zero out pitch and roll and convert it to a vector pointng forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);

	//Use rotation to get a Forward Vector from an FRotator using a FRotationMatrix
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//Use rotation to get a Right Vector from an FRotator using a FRotationMatrix
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	//Add the movement input to the controled pawn using the above Directions:
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, //World direction
										InputAxisVector.Y);//Scale value, Y component will be +1 or -1 wether pressing W or S. So scale by the Y Component
		ControlledPawn->AddMovementInput(RightDirection, 
										InputAxisVector.X);
	}
}
