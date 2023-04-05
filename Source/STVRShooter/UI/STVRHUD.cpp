// Fill out your copyright notice in the Description page of Project Settings.


#include "STVRHUD.h"

#include "Blueprint/UserWidget.h"

void ASTVRHUD::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = GetOwningPlayerController();
	// создаем экземпляр виджета
	if (WidgetClass != nullptr)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (Widget != nullptr)
		{
			// сохраняем ссылку на виджет в переменную
			const auto MyWidget = Widget;
			// добавляем виджет на экран
			MyWidget->AddToViewport();
			MyWidget->bIsFocusable=true;
			PlayerController->SetShowMouseCursor(true);
		}
	}
}
