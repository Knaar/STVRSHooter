#include "GladiatorCharacter.h"


#include "STVRPlayerController.h"
#include "UI/PlayerHealthWidget.h"
#include "Weapon/Weapon.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameUserSettings.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AGladiatorCharacter::AGladiatorCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	WeaponAttachmentPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachmentPoint"));
	WeaponAttachmentPoint->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	WeaponAttachmentPoint->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation=true;

	PlayerHealthWidgetComponent=CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHealthWidgetComponent"));
	PlayerHealthWidgetComponent->SetupAttachment(GetRootComponent());
	//PlayerHealthWidgetComponent->SetOwnerNoSee(true);
}

void AGladiatorCharacter::BeginPlay()
{
	Health=MaxHealth;
	
	Super::BeginPlay();
	if (WeaponClass != nullptr)
	{
		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
		Weapon->SetOwner(this);
		Weapon->AttachToComponent(WeaponAttachmentPoint,  FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	ServerChangeWidgetComponent_Implementation(GetHealth());

	ServerSetWidgetComponentVisibility();

	UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
	Settings->SetVSyncEnabled(true);
	Settings->ApplySettings(true);

	
}

void AGladiatorCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//ServerChangeWidgetComponent_Implementation(GetHealth());
}


void AGladiatorCharacter::Die()
{
	const auto PlayerController = Cast<ASTVRPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->DisableInput(nullptr);
	}
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UPostProcessComponent* PostProcessComponent = FindComponentByClass<UPostProcessComponent>();
	SetSaturation(0);
	
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGladiatorCharacter::RespawnCharacter, 5.0f, false);
}
void AGladiatorCharacter::RespawnCharacter()
{	
	APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
	if (!PlayerStart) return;
	
	const auto PlayerController = Cast<ASTVRPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->EnableInput(nullptr);
	}
	SetSaturation(1);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorLocation(PlayerStart->GetActorLocation());
	SetActorRotation(PlayerStart->GetActorRotation());
	Health=MaxHealth;
	EnableInput(Cast<APlayerController>(GetController()));
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	ServerChangeWidgetComponent_Implementation(GetHealth());
}





void AGladiatorCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGladiatorCharacter, Health);
}

/*
 * ShootingLogic
 */

void AGladiatorCharacter::ServerShoot_Implementation()
{
	MulticastShoot();
}

void AGladiatorCharacter::MulticastShoot_Implementation()
{
	Weapon->Shoot();
}

/*
 * Set 3D Widget Wisibility
 */

void AGladiatorCharacter::ServerSetWidgetComponentVisibility_Implementation()
{
	ClientSetWidgetComponentVisibility();
}

void AGladiatorCharacter::ClientSetWidgetComponentVisibility_Implementation()
{
	PlayerHealthWidgetComponent->SetVisibility(false);
}


/*
 * Change 3D Widget
 */



void AGladiatorCharacter::ServerChangeWidgetComponent_Implementation(float PercentValue)
{
	MulticastChangeWidgetComponent_Implementation(PercentValue);
}

void AGladiatorCharacter::MulticastChangeWidgetComponent_Implementation(float PercentValue)
{
	ChangeHealthWidget(PercentValue);
}

void AGladiatorCharacter::SetSaturation(double Value)
{
	if (CameraComponent)
	{
		
		CameraComponent->PostProcessSettings.ColorSaturation.Set(Value,Value,Value,Value);
	}
}


void AGladiatorCharacter::ChangeHealthWidget(float PercentValue)
{
	if (PlayerHealthWidgetComponent != nullptr)
	{
		Widget = Cast<UPlayerHealthWidget>(PlayerHealthWidgetComponent->GetUserWidgetObject());
		if (Widget != nullptr)
		{
			Widget->SetHealth(GetHealth());
			
		}
	}
}
/*
 * When the projectile touched the character
 */

void AGladiatorCharacter::MakeDamage(float Damage)
{
	if(HasAuthority())
	{
		ServerTakeDamage(Damage);
		
	}
	
}

void AGladiatorCharacter::ServerTakeDamage_Implementation(float Damage)
{
	MulticastTakeDamage(Damage);
	
}

void AGladiatorCharacter::MulticastTakeDamage_Implementation(float Damage)
{
	ApplyDamage(Damage);
	ServerChangeWidgetComponent_Implementation(GetHealth());
	
}

void AGladiatorCharacter::ClientTakeDamage_Implementation(float Damage)
{
}

void AGladiatorCharacter::ApplyDamage(float Damage)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		Health = 0.f;
		Die();
	}
	
}
