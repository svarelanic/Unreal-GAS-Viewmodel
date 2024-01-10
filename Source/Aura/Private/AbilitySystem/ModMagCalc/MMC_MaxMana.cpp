// Tutorial Project 


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	//Capture the Attribute:
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	//Define whether it is being captured from target or source
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	//Snapshotting has to do with timing. We can capture it when the GE is created or when it is applied. In this case we create it and apply it immediately
	IntelligenceDef.bSnapshot = false; //If true, we capture it as soon as GE is created

	//Our MMC needs an array of attributes to capture
	RelevantAttributesToCapture.Add(IntelligenceDef); //When modifier is executed when GE is applied, Vigor will be captured from the target at calculation time
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//We don't want to return Super, instead we want to return the custom calculation value

	//Getting the Attribute's value ----------
	
	//Gather GameplayTags from source AND target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//Filling in tag parameters for an in parameter to a function that Gets a captured Attribute's Value:
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	//Function will set the last parameter's value since it is an out parameter (passed by non const reference)
	float Intelligence = 0; //This value will be filled by GetCapturedAttributeMagnitude
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	//Usually these values get clamped for not getting negative values
	Intelligence = FMath::Max<float>(Intelligence, 0.f); //If Vigor is less than 0, we'll set it to 0

	//Getting a Variable (in this case level) ----------

	//We can get the Source Object of the EffectSpec and check if it implements the CombatInterface
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	//If the Cast is successful, it means the Character is implementing the Interface, so we can fetch the level
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//Now that we have the Attribute and the Variable, we decide the return calculation:
	return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
