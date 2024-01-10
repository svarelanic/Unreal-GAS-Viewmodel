// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h" //Implementing Interface, MUST define pure virtual functions
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public: 
	AAuraEnemy();

	//From IEnemyInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/** CombatInterface */
	//Overriding GetLevel from CombatInterface for using in GameplayEffect MMC
	virtual int32 GetPlayerLevel() override;
	/** CombatInterface */
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	//Enemy level variable that will determine the value of certain Attributes
	//With a CombatInterface we'll retrieve the level of whatever implements it and
	//create an MMC (custom calculation) for Attributes
	//Level resides in PlayerState only for player controller character. Enemies will have it on the Character itself
	//We do not replicate this one since we are checking enemy levels on Server only
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;
};
