// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  AuraGameplayTags
 *
 *  Singleton containing native Gameplay Tags (created from within and available on C++)
 */

struct FAuraGameplayTags
{
public:
 //This is a Singleton, so we'll create a Static Getter that return the one and only instance that exists
 static const FAuraGameplayTags& Get() {return GameplayTags; }

 //To initialize our Gameplay Tags -> because it is static, it can be called without one of this type in existence
 static void InitializeNativeGameplayTags();

 //To store specific attribute info:
 
 //Primary Attributes
 FGameplayTag Attributes_Primary_Strength;
 FGameplayTag Attributes_Primary_Intelligence;
 FGameplayTag Attributes_Primary_Resilience;
 FGameplayTag Attributes_Primary_Vigor;
 
 //Secondary Attributes
 FGameplayTag Attributes_Secondary_MaxHealth;
 FGameplayTag Attributes_Secondary_MaxMana;
 FGameplayTag Attributes_Secondary_Armor;
 FGameplayTag Attributes_Secondary_ArmorPenetration;
 FGameplayTag Attributes_Secondary_BlockChance;
 FGameplayTag Attributes_Secondary_CriticalHitChance;
 FGameplayTag Attributes_Secondary_CriticalHitDamage;
 FGameplayTag Attributes_Secondary_CriticalHitResistance;
 FGameplayTag Attributes_Secondary_HealthRegeneration;
 FGameplayTag Attributes_Secondary_ManaRegeneration;

 //Tags to find PlayerInput and assign a GameplayAbility to it
 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;

protected:

private:
 //Stores the only instance that exists of this class, returned on the Get function.
 //The type musts be explicitly declared on the cpp file
 static FAuraGameplayTags GameplayTags;
 
};
