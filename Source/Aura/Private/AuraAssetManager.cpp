// Tutorial Project 


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	//Returns the engine's AssetManager, we'll cast it to the UAuraAssetManager type
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager; //Function does not return a pointer, it returns a Reference, so dereference it
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Call InitializeNativeGameplayTags from AuraGameplayTags
	FAuraGameplayTags::InitializeNativeGameplayTags();
}


