// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	//MaxHealth Attribute will be determined by the calculation we do in this Custom Calculation

public:
	//Constructor
	UMMC_MaxHealth();

	//Where we put our calculation. Returns the result our modifier should produce
	//Input value is the EffectSpec of whatever GE that has a modifier using this Custom Calculation
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	//MMCs can capture attributes in a variable
	FGameplayEffectAttributeCaptureDefinition VigorDef;

};
