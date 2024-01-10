// Tutorial Project 

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	//This is a Singleton, which requires a static getter that returns an AuraAssetManager reference to the one and only.
	static UAuraAssetManager& Get();

protected:
	//to start initialization for our assets. This is the best place to call InitializeNativeGameplayTags
	virtual void StartInitialLoading() override;
};
