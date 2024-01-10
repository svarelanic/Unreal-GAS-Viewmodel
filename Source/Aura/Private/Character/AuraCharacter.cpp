// Tutorial Project 


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	//Settings for Character Movement from the CharaterMovementComponent:

	GetCharacterMovement()->bOrientRotationToMovement = true; //Rotates to point towards where it is moving
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); //Speed at which it rotates to point towards movement. Should be tweeked in the editor
	GetCharacterMovement()->bConstrainToPlane = true; //This is what we want in top down games 
	GetCharacterMovement()->bSnapToPlaneAtStart = true; //Only works if bConstrainToPlane is enabled

	//Character should not use the Controller's rotation:
	bUseControllerRotationPitch = false; 
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//For a fixed Camera, in the Spring Arm component in the Editor
	//uncheck the Inherit Pitch, Yaw and Raw Camera Settings
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init Ability Actor Info for the Server
	InitAbilityActorInfo();

	//Add Abilities to our Character's StartupAbilities array
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel()
{
	//The Level for the Character is in the PlayerState
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); //Template function from AController class
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	//Get the PlayerState:
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); //Template function from AController class
	check(AuraPlayerState);

	//From the PlayerState, get the ASC and initialize the Ability Actor Info from ASC
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	//Cast AuraCharacter to AuraAbilitySystemComponent and call the function that
	//will bind a callback function to a delegate when a GameplayEffect is applied
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())-> AbilityActorInfoSet();
	
	//Setting the ASC and AS Components from the PlayerState
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	//Call InitOverlay, where we create the OverlayWidget and its Controller, linking
	//both as well
	//Check PlayerController for Client, as in Client all other PlayerControllers of
	//other machines do not have valid PlayerControllers (it can and will be null in multiplayer)
	if(AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	//Setting init values for primary AND secondary attributes using function from base class
	InitializeDefaultAttributes();
}
