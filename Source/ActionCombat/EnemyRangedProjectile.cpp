// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRangedProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AEnemyRangedProjectile::AEnemyRangedProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyRangedProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyRangedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyRangedProjectile::HandleBeginOverlap(AActor* OtherActor){
	APawn* PawnRef = Cast<APawn>(OtherActor);
	
	if(!PawnRef->IsPlayerControlled()){
		return;
	}
	
	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();

	FTimerHandle DeathTimerHandle{};
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEnemyRangedProjectile::DestroyProjectile, 0.5f);
	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FDamageEvent TargetAttackEvent;
	PawnRef->TakeDamage(ProjectileDamage, TargetAttackEvent,  PawnRef->GetController(), this);
}
void AEnemyRangedProjectile::DestroyProjectile(){
	Destroy();
}