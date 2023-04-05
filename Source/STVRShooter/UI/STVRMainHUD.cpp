// Fill out your copyright notice in the Description page of Project Settings.


#include "STVRMainHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "STVRShooter/GladiatorCharacter.h"

void ASTVRMainHUD::BeginPlay()
{
	Super::BeginPlay();
	MakeInGameWidget();
	}

void ASTVRMainHUD::MakeInGameWidget()
{
	
	if(InGameHealthWidgetClass)
	{
		// Создаем экземпляр виджета
		HealthWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), InGameHealthWidgetClass);
	
		// Добавляем виджет на экран
		HealthWidget->AddToViewport();
	}
}

