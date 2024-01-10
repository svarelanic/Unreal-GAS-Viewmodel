// Tutorial Project 

#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h" //For ASC
#include "AbilitySystem/AuraAttributeSet.h" //For AS
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	//Setting collisions to Block Visibility so we can interact when hovering over with cursor
	//with the cursor trace defined in the PlayerController, where we check if said Actor implements
	//IEnemyInterface
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//Constructing Ability System Component and Attribute Set
	// These are populated with Data only in AuraEnemy and not in AuraCharacter class (since we'll use PlayerState there)
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); //We want the ASC to Replicate
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

}

void AAuraEnemy::InitAbilityActorInfo()
{
	//Initializing Actor Info so the ASC knows who owns it
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	//Cast AuraCharacter to AuraAbilitySystemComponent and call the function that
	//will bind a callback function to a delegate when a GameplayEffect is applied
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
}

void AAuraEnemy::HighlightActor()
{
	//To Highlight an Actor, we'll be using a Material called PP_Highlight that highlights in Red
	//when the Depth Stencil Value is set to 250 in the Editor. So we'll enable it and set it 
	//to 250 in this function and disable it in UnHighlightActor
	//For the Highlight to show we must also add a Post Process Volume to the world and set the 
	//Custom Depth-Stencil Pass to 'Enabled with Stencil' on Project Settings

	GetMesh()->SetRenderCustomDepth(true); //Enable the Custom Depth
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);// Set the Stencil Value to 250 to activate the highlight
	
	//Handle the weapon as well:
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false); //Disable the Custom Depth to hide the Highlight
	Weapon->SetRenderCustomDepth(false); //Hide from Weapon as well
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}
