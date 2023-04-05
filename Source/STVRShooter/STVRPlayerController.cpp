// Fill out your copyright notice in the Description page of Project Settings.


#include "STVRPlayerController.h"

#include "GladiatorCharacter.h"

void ASTVRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForward"),this,&ASTVRPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"),this,&ASTVRPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("Turn"),this,&ASTVRPlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUp"),this,&ASTVRPlayerController::LookUp);
	InputComponent->BindAction(TEXT("Shoot"),IE_Pressed,this,&ASTVRPlayerController::Shoot);
}

void ASTVRPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		APawn* PlayerPawn = GetPawn();
		if (PlayerPawn != nullptr)
		{
			PlayerPawn->AddMovementInput(PlayerPawn->GetActorForwardVector() * Value);
		}
	}
}

void ASTVRPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		APawn* PlayerPawn = GetPawn();
		if (PlayerPawn != nullptr)
		{
			PlayerPawn->AddMovementInput(PlayerPawn->GetActorRightVector() * Value);
		}
	}
}

void ASTVRPlayerController::Turn(float Value)
{
	APawn* PlayerPawn = GetPawn();
	if (PlayerPawn != nullptr)
	{
		PlayerPawn->AddControllerYawInput(Value);
	}
}

void ASTVRPlayerController::LookUp(float Value)
{
	APawn* PlayerPawn = GetPawn();
	if (PlayerPawn != nullptr)
	{
		PlayerPawn->AddControllerPitchInput(Value);
	}
}

void ASTVRPlayerController::Shoot()
{
	APawn* PlayerPawn = GetPawn();
	if (PlayerPawn != nullptr)
	{
		AGladiatorCharacter* GladiatorCharacter = Cast<AGladiatorCharacter>(PlayerPawn);
		if (GladiatorCharacter != nullptr)
		{
			GladiatorCharacter->ServerShoot();		}
	}
}

