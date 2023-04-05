#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "STVRShooter/GladiatorCharacter.h"

AProjectile::AProjectile()
{
	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	// Устанавливаем коллизию только на снаряде
	StaticMeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this,&AProjectile::OnOverlap);
	// Создаем компонент для движения снаряда
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
  
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	// Устанавливаем время жизни снаряда
	InitialLifeSpan = 3.0f;
	
}

void AProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& amp)
{
	
  
	const auto Victim=Cast<AGladiatorCharacter>(OtherActor);
	if(Victim)
	{
		Victim->MakeDamage(ProjectileDamage);
		
		Destroy();
		
	}
	
}
