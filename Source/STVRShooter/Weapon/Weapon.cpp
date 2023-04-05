#include "Weapon.h"
#include "Projectile.h"
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	MuzzleSocket=CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	MuzzleSocket->SetupAttachment(RootComponent,TEXT("Muzzle"));
	SetReplicates(true);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Shoot()
{
	if (ProjectileClass == nullptr) return;
	FVector Location = Mesh->GetSocketLocation(TEXT("Muzzle"));
	FRotator Rotation = Mesh->GetSocketRotation(TEXT("Muzzle"));
		
	FActorSpawnParameters SpawnParams;
		
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
		
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation, SpawnParams);
	if (Projectile != nullptr)
	{
		Projectile->SetInstigator(GetInstigator());
		FVector LaunchDirection = Rotation.Vector();
		Projectile->ProjectileMovementComponent->Velocity = LaunchDirection * ProjectileSpeed;
		UE_LOG(LogTemp,Warning,TEXT("Shooted"));
	}
	
}




