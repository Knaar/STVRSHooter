// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthWidget.generated.h"

class AGladiatorCharacter;
class UProgressBar;

UCLASS()
class STVRSHOOTER_API UPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	

	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealthValue);
	
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	AGladiatorCharacter* Character;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
};


