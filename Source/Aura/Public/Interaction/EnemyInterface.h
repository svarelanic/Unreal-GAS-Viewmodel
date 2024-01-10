// Tutorial Project 

//This Interface will be used when hovering over enemies, allowing the Title to highlight them
//When hovering over an actor, the PlayerController checks if said actor implements this
//interface and, if it doea, it should call an interface function which the highlighted Actor
//can then overrride and implement in any way it wants (different Actors implementing this Interface
// can implement the function however way they want)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//Hihglight the enemy when hovering over it
	virtual void HighlightActor() = 0; //Pure virtual function, we will not provide a definition here 
										//and will be derived from the inheriting class, 
										//which MUST override it and provide a definition
	
	//UnHighlight enemy when not hovering over it
	virtual void UnHighlightActor() = 0;
};

