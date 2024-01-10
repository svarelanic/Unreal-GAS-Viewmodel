// Tutorial Project 


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Construct the Weapon mesh component
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//Attach it to a socket on the mesh
	Weapon->SetupAttachment(GetMesh(), //Character's mesh we attach to
							FName("WeaponHandSocket")); //Socket we attach to, we'll add it to the Character's SKM
	//Remove weapon's collisions:
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	//We'll need a GameplayEffect Spec to apply which we can create since we have a class
	//for our default primary attributes. To make the EffectSpec we need a ContextHandle
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	//Set SourceObject to call GetSourceObject to check for interface implementation and retrieving data
	ContextHandle.AddSourceObject(this); //The source object is the class that has the implemented function 
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);//Must be initialized after PrimaryAttributes since values here depend on them 
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f); //Must be initialized after SecondaryAttributes since values here depend on them 
}

void AAuraCharacterBase::AddCharacterAbilities()
{

	//Access the ASC to call function from it
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	
	//Should only add abilities on the SERVER
	if(!HasAuthority())
	{
		return;
	}

	//If it is on the server, call function from AbilitySystemComponent that adds the StartUp Abilities.
	AuraASC->AddCharacterAbilities(StartupAbilities);
}



