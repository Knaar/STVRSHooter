// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpectatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STVRSHOOTER_API USpectatorComponent : public UActorComponent
{
	GENERATED_BODY()
 /*
public:
	// Sets default values for this component's properties
	USpectatorComponent();
 
	// Called when the game starts
	virtual void BeginPlay() override;
 
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
 
	// Start spectating
	void StartSpectating();
 
	// Stop spectating
	void StopSpectating();
 
private:
	// Camera parameters
	FVector CameraLocation;
	FRotator CameraRotation;
	float CameraFOV;
 
	// Player controller
	APlayerController* PlayerController;
	*/
};
