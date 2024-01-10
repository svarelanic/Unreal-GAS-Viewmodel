// Tutorial Project 


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	//Find ability info struct in our array that has the correct AttributeTag using a for loop
	for (const FAuraAttributeInfo& Info : AttributeInformation) //Check Info struct against AttributeInformation array
	{
		if(Info.AttributeTag.MatchesTagExact(AttributeTag)) //If the Tags match
		{
			return Info;
		}
	}

	//Made it through the loop and never found an AttributeInfo Struct in the Array
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for the AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo(); //Return an empty FAuraAttributeInfo struct
}
