// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePrototype/Public/UI/BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
