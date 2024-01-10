// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
//Forward declaring for ASC and AS
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract) //Prevents class from being dragged into the level -> Useful for base classes
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	//Getters for the AbilitySytemComponent and the AttributeSet---------------
	//Overridign GetAbilitySystemComponent from the IAbilityInterface 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//Simple getter for AttributeSet:
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	//Skeletal mesh component for weapon, we will attach to a socket in the character's mesh
	//Using TObject pointer for access tracking (checking how many times a pointer is accessed) and lazy loading (An asset cannot be loaded until needed or used in program)
	//Standard is moving towards TObject pointers for member variables
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//Pointers to store the Ability System Component and the Attribute Set 
	//Will be inherited by all Characters, but not all of them have to construct them
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//Declaring function to Initialize AbilityActorInfo and then override in child classes
	virtual void InitAbilityActorInfo();

	//To Initialize Attributes by Applying a GameplayEffect at the start
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	
	//To apply GameplayEffect that initializes Attributes:
	//This class will hold the init values for primary attributes. All these attributes
	//are marked to be replicated, so changing them on Server will change them on client
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes; //Set it on BP 
	

	//To apply GameplayEffect that initializes Secondary Attributes -> Will be and Infinite Effect
	//This class will initialize default values of derived attributes when the primary attributes they depend on change. All these attributes
	//are marked to be replicated, so changing them on Server will change them on client
	//Must initialize after primary attributes so their update triggers
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes; //Set it on BP

	//To apply GameplayEffect that initializes Vital Attributes -> Will be and Instant Effect since we just need to set them at the start
	//This class will initialize default values of derived attributes when the primary attributes they depend on change. All these attributes
	//are marked to be replicated, so changing them on Server will change them on client
	//Must initialize after primary attributes so their update triggers
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes; //Set it on BP

	//Initializing both Primary and Secondary Attributes (primary attributes initialized before secondary attributes)
	void InitializeDefaultAttributes() const;

	
	//To add Abilities to the StartupAbilities array
	//Call this on a Player Possessed Character (AuraCharacter) on PossessedBy() function
	void AddCharacterAbilities();
	
private: 
	//TArray to set on BP that holds our Abilities available on application startup
	//We give it Abilities through the AbilitySystemComponent in a function here, in AuraCharacterBase
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
