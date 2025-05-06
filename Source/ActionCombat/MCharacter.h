// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.h"
#include "Fighter.h"
#include "MCharacter.generated.h"


UCLASS()
class ACTIONCOMBAT_API AMCharacter : public ACharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UAnimMontage* DeathAnimMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* HurtAnimMontage;
public:
	// Sets default values for this character's properties
	AMCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStatsComponent* StatsComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBlockComponent* BlockComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class ULockOnComponent* LockonComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTraceComponent* TraceComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPlayerActionsComponent* PlayerActionsComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
	class UPlayerAnimInstance* PlayerAnim;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;
	virtual bool HasEnoughStamina(float StaminaCost) override;

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	virtual void EndLockonWithActor(AActor* ActorRef) override;
	virtual bool CanTakeDamage(AActor* Opponent) override;
	UFUNCTION(BlueprintCallable)
	void PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate);
};	
