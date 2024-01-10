// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	//constructor
	UMMC_MaxMana();

	//Where we put our calculation. Returns the result our modifier should produce
	//Input value is the EffectSpec of whatever GE that has a modifier using this Custom Calculation
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	//MMCs can capture attributes in a variable
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};
