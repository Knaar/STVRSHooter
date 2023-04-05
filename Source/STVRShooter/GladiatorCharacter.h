// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GladiatorCharacter.generated.h"


class UPlayerHealthWidget;
class UWidgetComponent;
class AWeapon;

DECLARE_DELEGATE(FSayHelloDelegate);

UCLASS()
class STVRSHOOTER_API AGladiatorCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AGladiatorCharacter();
protected:
	UPROPERTY()
	USceneComponent* WeaponAttachmentPoint;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

	//Widgets
	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> PlayerHealthWidgetClass;

	UPROPERTY(EditAnywhere,Replicated, BlueprintReadWrite, Category = "Widgets")
	UWidgetComponent* PlayerHealthWidgetComponent;

	UPROPERTY()
	UPlayerHealthWidget* Widget;

	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	void Die();
	void RespawnCharacter();
		
	FTimerHandle TimerHandle_Respawn;
	UFUNCTION(BlueprintCallable)
	void SetSaturation(double Value);
	
	UFUNCTION(Server, Reliable)
	void ServerShoot();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastShoot();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const {return Health/MaxHealth;};
	
	//Set 3D Widget Visibility

	UFUNCTION(Server,Unreliable)
	void ServerSetWidgetComponentVisibility();

	UFUNCTION(Client,Unreliable)
	void ClientSetWidgetComponentVisibility();
	
	//UpdateWidgetComponent

	UFUNCTION(Server, Reliable)
	void ServerChangeWidgetComponent(float PercentValue);

	UFUNCTION(NetMulticast,Reliable)
	void MulticastChangeWidgetComponent(float PercentValue);

	void ChangeHealthWidget(float PercentValue);

	//TryToMakeDamage

	
	UFUNCTION(BlueprintCallable)
	void MakeDamage(float Damage);

	UFUNCTION(Server,Reliable)
	void ServerTakeDamage(float Damage);

	UFUNCTION(NetMulticast,Reliable)
	void MulticastTakeDamage(float Damage);

	UFUNCTION(Client,Reliable)
	void ClientTakeDamage(float Damage);
	
	void ApplyDamage(float Damage);

	
	
};