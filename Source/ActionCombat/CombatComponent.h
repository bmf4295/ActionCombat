// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<class UAnimMontage*> AttackAnimations;

	ACharacter* CharacterRef;

	UPROPERTY(VisibleAnywhere)
	int32 ComboCounter = 0;
	
	UPROPERTY(VisibleAnywhere)
	bool bCanAttack = true;
public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ComboAttack();
		
	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();
};
