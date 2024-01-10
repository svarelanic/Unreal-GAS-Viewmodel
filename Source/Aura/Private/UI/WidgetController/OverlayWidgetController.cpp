// Tutorial Project 


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//No need to call Super since its empty	
	//We'll broadcast values for Health and Mana Widgets, so we'll use Delegates to
	//do so
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet -> GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet -> GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet -> GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet -> GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//Get the Attribute Set
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// create the Delegate with GetGameplayAttributeValueChangeDelegate (passing in the
	// Attribute) and then broadcast using AddLamda

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->
	GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		//When Health changes, we'll want to Broadcast the OnHealthChanged Delegate so my
		//Widgets can respond to it

		OnHealthChanged.Broadcast(Data.NewValue); //This NewValue Data gets us the new value
												  //that has changed for the attribute
												  //which will be Broadcasted to update the UI
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->
	GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		//When MaxHealth changes, we'll want to Broadcast the OnHealthChanged Delegate so my
		//Widgets can respond to it
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}); 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->
	GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->
	GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});

	//Binding WidgetController to AssetTags Delegate to broadcast GameplayEffects to the
	//HUD:
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this] //capture this object to use its member variables and functions
		(const FGameplayTagContainer& AssetTags)//Where input parameters go
		{
			//Here we can define the functionality being executed on Broadcast
			for(const FGameplayTag& Tag : AssetTags) //Go through the Tag Container
			{
				//Restrict for using only Message tags 
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if(Tag.MatchesTag(MessageTag))
				{
					//Take a DataTable and a Gameplay Tag, and return the Row:
					//To call member functions in AddLambda, we must know member functions in the
					//square brackets. 
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);

					//Broadcast the Row from the Message DataTable
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
		);
}

