// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STVRHUD.generated.h"


UCLASS()
class STVRSHOOTER_API ASTVRHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> WidgetClass;
	
	void BeginPlay();
};
