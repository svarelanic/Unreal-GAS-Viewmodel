// Tutorial Project 


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h" //For Getting Aura's attribute Set
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	//Creating a simple Scene Root Component for ease of use on BP by Designers
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//Check if the Overlapping actor implements the IAbilitySystemInterface, if it does,
	//take the actor's ASC and implement the Effect
	//This function casts actor to IAbilitySystemInterface automatically and returns the
	//ASC from it, returning early if it does not. It is BlueprintCallable
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC==nullptr)
	{
		return;
	}

	//Check the TSubclassOf GameplayEffectClass was set correctly on BP:
	check(GameplayEffectClass);
	
	//Applying Gameplay Effect:

	//To make the GameplayEffect using MakeOutgoingSpec, we'll need to make a
	//GameplayEffectContext first. This function returns a Handle to said Context
	//The handle is a lightweight wrapper that stores the actual EffectContext as a pointer
	FGameplayEffectContextHandle EffectContextHandle =  TargetASC->MakeEffectContext();

	//Setting parameters on the EffectContext:
	EffectContextHandle.AddSourceObject(this); //To check what object caused the Effect
	
	//GameplayEffectSpec can be made with the ASC
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

	//Finally apply the effect to the TargetASC
	//Get the EffectSpec from the EffectSpecHandle and dereference it
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//Storing Effect and Actor if Effect is Infinite to then Remove the Effect OnEndOverlap
	
	//Check if GameplayEffect is InifniteDuration. Def is the GameplayEffect
	//itslef from the EffectSpec
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//Store the EffectHandle and TargetActor's AbilitySystemComponent pointer in a Map
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	//For Instant Effect:
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		//If policy is ApplyOnOverlap, we'll want to ApplyEffectToTarget here
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	//For Duration Effect:
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{ 
		//If policy is ApplyOnOverlap, we'll want to ApplyEffectToTarget here
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	//For Infinite Effect:
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		//If policy is ApplyOnOverlap, we'll want to ApplyEffectToTarget here
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	//For Instant Effect:
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		//If policy is ApplyOnEndOverlap, we'll want to ApplyEffectToTarget here
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	//For Duration Effect:
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		//If policy is ApplyOnOverlap, we'll want to ApplyEffectToTarget here
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	//For Infinite Effect Application:
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		//If policy is ApplyOnOverlap, we'll want to ApplyEffectToTarget here
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	//For Infinite Effect Removal:
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//Get the TargetActor's ASC and check it against key value pair in our
		//ActiveEffectHandles Map:
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC))
		{
			return;
		}

		//Array to accumulate Map Key value pairs to remove after For loop
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		for(TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair:ActiveEffectHandles)
		{
			//Check local TargetASC against map key ASC value
			//HandlePair.Value is the TargetActor's ASC in the Map
			if(TargetASC == HandlePair.Value)
			{
				//Remove the Effect. HandlePlair.Key is the GameplayEffect in the Map
				//second parameter removes a single Stack instead of all of them at once
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);

				//After removing the Effect, we want to remove the pair from the Map as well
				//We'll accumulate key value pairs we want to remove in a container and remove the
				//pairs after the for loop to evade crashes
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		//For loop to Remove handles of Effects already removed
		for (FActiveGameplayEffectHandle& Handle:HandlesToRemove)
		{
			//Removing pairs added after GameplayEffect was removed
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}


