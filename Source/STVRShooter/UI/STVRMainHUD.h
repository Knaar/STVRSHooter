// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STVRMainHUD.generated.h"


UCLASS()
class STVRSHOOTER_API ASTVRMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	void MakeInGameWidget();
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widgets")
	TSubclassOf<UUserWidget> InGameHealthWidgetClass;

	UUserWidget* HealthWidget;
};
