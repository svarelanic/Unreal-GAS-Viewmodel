// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h" //For FActiveGameplayEffectHandle
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

//ENUM classes for the Effect Application and Effect Removal policy
UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	//Constants for our Policy. Create a Variable of these types for each EffectClass
	//to set the Policy on Blueprint
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

//Applies only to infinite effects:
UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	//Constants for our Policy. Create a Variable of these types for each EffectClass
	//to set the Policy on Blueprint
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{

	//This Actor will be mostly handled by the Designers, so there won't be much functionality
	//from the code's side. Make it flexible and easy to configure from BP.
	
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;
	
	//Function to Apply the Gameplay Effect. We can call it from BP when overlapping
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	//Functions to handle Overlap and EndOverlap to call from BP 
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	//To handle Actor Destruction after Effect removal
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	bool bDestroyOnEffectRemoval = false;
	
	//Class for Effects to apply and its enum application/removal policy,
	//which will be set on BP:
	//We want to create the GameplayEffect itself on BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	//Map to store both GameplayEffectHandle and its corresponding TargetActor's ASC
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	//A level for the Actor that determines the Magnitude or properties of the Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	float ActorLevel = 1.f;
private:
	
};
