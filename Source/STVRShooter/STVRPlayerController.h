// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STVRPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STVRSHOOTER_API ASTVRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	virtual void SetupInputComponent() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Shoot();
	
};
