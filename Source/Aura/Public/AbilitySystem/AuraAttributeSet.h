// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


//Define for the use of ACCESSORS for Attributes
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//STRUCT for data obtained after GameplayEffect changes an attribute.
//We get it via the Data from PostGameplayEffectExecute() function and store it
//into the STRUCT's variables using SetEffectProperties
//Depending on what caused the Effect, it might not be a Character or not have a Controller
//so we added the checks 
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};


//Template to substitute a type's syntax. It's a function pointer capable of storing the address of a function of any function signature we choose
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	
	//Function where we Register Variables for Replication using DOREPLIFETIME
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//For clamping only (restricting between two values) Attributes
	//Whenever any attribute changes, this function kicks off in response before the
	//change occurs (regardless of the reason why) -> Never use for kicking off logic
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//Executed AFTER a GameplayEffect changes an attribute. Data holds info depending on the
	//effect applied, including the ASC of the TargetActor and info about the Source
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	//MOST Attributes must be replicated, and replication can only be done using RepNotifies
	//When the Attribute changes and is replicated to the Server, the RepNotify is called.
	//In the RepNotify, the old value for the Replicated Attribute is saved in its input value. 


	
	//Binding Gameplay Tags to our Attributes for displaying in UI----------------------------------------- 

	//To Map Gameplay Tags with static Getter functions that return FGameplayAttribute type
	//Add key values to this map in the Constructor
	//Value is a template type capable of storing the address of a function of any function signature we choose
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;


	
	//Attributes ------------------------------------------------------------------------------

	//Primary Attributes

	//Strength Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	//Intelligence Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	//Resilience Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	//Vigor Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;



	
	//Vital Attributes

	//Health Attribute:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	//ACCESSOR MACRO for Attribute
	//Acts as Getter, Setter, Initializer and Getter for the Attribute object itself.
	//Init sets Base and Current Value,while Set sets Base Value only:
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	//RepNotify for Health Attribute
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//Mana Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	//RepNotify for Mana Attribute
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;


	//Secondary Attributes
	
	//Max Health Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	//RepNotify for MaxHealth Attribute
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//MaxMana Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	//RepNotify for MaxMana
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	//Armor Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	//RepNotify for Armor
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	//ArmorPenetration Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	//RepNotify for ArmorPenetration
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	//BlockChance Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	//RepNotify for BlockChance
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	//CriticalHitChance Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	//RepNotify for CriticalHitChance
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	//CriticalHitDamage Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	//RepNotify for CriticalHitDamage
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	//CriticalHitResistance Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	//RepNotify for CriticalHitResistance
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	//HealthRegeneration Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	//RepNotify for HealthRegeneration
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	//ManaRegeneration Attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	//Accessor
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	//RepNotify for ManaRegeneration
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

private:
	//To fill the FEffectProperties struct
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& props) const;
};


