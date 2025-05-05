// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyRangedProjectile.generated.h"

UCLASS()
class ACTIONCOMBAT_API AEnemyRangedProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitTemplate;
	
	UPROPERTY(EditAnywhere)
	float ProjectileDamage = 10.0f;

public:	
	// Sets default values for this actor's properties
	AEnemyRangedProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);

	UFUNCTION()
	void DestroyProjectile();

};
