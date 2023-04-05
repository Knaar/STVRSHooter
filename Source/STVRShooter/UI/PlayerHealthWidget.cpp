// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthWidget.h"

#include "Components/ProgressBar.h"
#include "STVRShooter/GladiatorCharacter.h"

void UPlayerHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Character = Cast<AGladiatorCharacter>(GetOwningPlayerPawn());
}



void UPlayerHealthWidget::SetHealth(float NewHealthValue)
{
	
	HealthBar->SetPercent(NewHealthValue);
	if (NewHealthValue > 0.5f)
	{
		HealthBar->SetFillColorAndOpacity(FLinearColor::Green);
	}
	else if (NewHealthValue > 0.2f)
	{
		HealthBar->SetFillColorAndOpacity(FLinearColor::Yellow);
	}
	else
	{
		HealthBar->SetFillColorAndOpacity(FLinearColor::Red);
	}
}
