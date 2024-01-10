// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

//Forward declaring for ASC and AS
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public: 
	AAuraPlayerState();

	//Overriding to replicate variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//Getters for the AbilitySytemComponent and the AttributeSet---------------
	//Overridign GetAbilitySystemComponent from the IAbilityInterface 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//Simple getter for AttributeSet:
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	//Getter for the Level variable, which we'll get on the AuraCharacter class
	FORCEINLINE int32 GetPlayerLevel() const {return Level;}

protected:
	
	//Pointers to store the Ability System Component and the Attribute Set 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	//Player level variable that will determine the value of certain Attributes
	//With a CombatInterface we'll retrieve the level of whatever implements it and
	//create an MMC (custom calculation) for Attributes
	//Level resides in PlayerState only for player controller character. Enemies will have it on the Character itself
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	//Rep notify to replicate level
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	
};
