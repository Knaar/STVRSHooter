// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"


#include "Projectile.generated.h"
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class STVRSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
public:
	AProjectile();

	
	// Variables
	
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileDamage = 10.f;

	bool bIsOverlapHandled = false;
	// Components
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
	// Methods
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& amp);
	
};
