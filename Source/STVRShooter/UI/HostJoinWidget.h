// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HostJoinWidget.generated.h"

UCLASS()
class STVRSHOOTER_API UHostJoinWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

private:
	
	FString Path="/Game/Maps/FirstPersonMap?Listen";
	FString Address="127.0.0.1";
	FString DedicatedAddress="217.65.3.221:7777";
	
public:
	UFUNCTION(BlueprintCallable)
	void OpenLobby();
	
	UFUNCTION(BlueprintCallable)
	void CallClientTravel();
	
	UFUNCTION(BlueprintCallable)
	void CallDedicatedTravel();
};
