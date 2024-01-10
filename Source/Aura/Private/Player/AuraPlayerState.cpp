// Tutorial Project 


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h" //For ASC
#include "AbilitySystem/AuraAttributeSet.h" //For AS
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	//Constructing Ability System Component and Attribute Set
	//These pointers must also be set on AuraCharacter
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); //We want the ASC to Replicate
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	//Setting Net Update Frequency: How often Server will try to update Clients
	//Normally, in the Player State it will be set to a lower value BUT
	//when Ability System Component and Attribute Set are added to Player State, its 
	//NetUpdateFrequency will be set much higher, ex: Lyra and Fortnite.
	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Marking Level variable for replication
	DOREPLIFETIME(AAuraPlayerState, Level);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
