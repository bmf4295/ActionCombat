// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{0.f};

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat =false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection{0.f};

	public:
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewActor);
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsBlocking =false;

};
