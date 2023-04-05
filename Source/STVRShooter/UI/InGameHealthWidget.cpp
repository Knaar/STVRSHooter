// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHealthWidget.h"

#include "Components/ProgressBar.h"
#include "STVRShooter/GladiatorCharacter.h"


void UInGameHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Character = Cast<AGladiatorCharacter>(GetOwningPlayerPawn());
}

void UInGameHealthWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	HealthBar->SetPercent(Character->GetHealth());
}
