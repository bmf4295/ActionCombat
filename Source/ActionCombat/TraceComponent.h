// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()
	class USkeletalMeshComponent* SkeletalComp; 

	UPROPERTY(EditAnywhere)
	FName Start; 

	UPROPERTY(EditAnywhere)
	FName End; 

	UPROPERTY(EditAnywhere)
	FName Rotation; 

	UPROPERTY(EditAnywhere)
	double BoxWidth = 30.0; 

	UPROPERTY(EditAnywhere)
	double BoxHeight = 30.0; 
	
	UPROPERTY(EditAnywhere)
	bool bDebugMode = false;

	TArray<AActor*> TargetToIgnore;

public:	
	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();
	
	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking= false;
		
};
