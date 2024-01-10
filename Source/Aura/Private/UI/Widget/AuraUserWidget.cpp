// Tutorial Project 


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	//We'll set Widget Controller with the Setter, we make sure that when implementing
	//WidgetControllerSet in any BP, we know our WidgetController will be Set. 
	WidgetController = InWidgetController;
	WidgetControllerSet();

}


