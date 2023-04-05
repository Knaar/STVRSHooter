// Fill out your copyright notice in the Description page of Project Settings.


#include "SpectatorComponent.h"

#include "GameFramework/SpectatorPawn.h"
/*
#include "MySpectatorPawn.h"
#include "SpectatorController.h"
#include "Kismet/GameplayStatics.h"
void USpectatorComponent::StartSpectating()
{
	// Get player controller
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// Save current camera parameters
	CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	CameraFOV = PlayerController->PlayerCameraManager->GetFOVAngle();
	// Create new spectator pawn
	AMySpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<AMySpectatorPawn>(AMySpectatorPawn::StaticClass());
	SpectatorPawn->SetActorLocation(CameraLocation);
	SpectatorPawn->SetActorRotation(CameraRotation);
	// Set new camera parameters
	SpectatorPawn->GetCameraComponent()->SetFieldOfView(CameraFOV);
	// Set player controller to spectator controller
	PlayerController->UnPossess();
	PlayerController->Possess(SpectatorPawn);
}
*/