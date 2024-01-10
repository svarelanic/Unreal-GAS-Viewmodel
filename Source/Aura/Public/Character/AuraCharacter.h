// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public: 
	AAuraCharacter();

	//Override PossessedBy and OnRep_PlayerState() to initialize the Ability Actor Info so ASC can know its owner
	//PossessedBy is from the Pawn class and is called when the Character is possessed by a Controller
	virtual void PossessedBy(AController* NewController) override; //For the Server
	virtual void OnRep_PlayerState() override; //For the Client

	/** CombatInterface */
	//Overriding GetLevel from CombatInterface for using in GameplayEffect MMC
	virtual int32 GetPlayerLevel() override;
	/** CombatInterface */

private:
	//Function to Get PlayerState, from it get the ASC and initialize Ability Actor Info, also
	//setting the ASC and AS variables of AuraCharacterBase from the PlayerState
	virtual void InitAbilityActorInfo() override;
};
