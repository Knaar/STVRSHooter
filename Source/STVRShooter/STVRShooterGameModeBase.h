// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STVRShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STVRSHOOTER_API ASTVRShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

};
