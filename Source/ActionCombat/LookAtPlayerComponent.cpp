// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtPlayerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();



	
}


// Called every frame
void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(!bCanRotate){
		return;
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* OwnerRef = 	GetOwner();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	FVector OwnerLocation = OwnerRef->GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();

	FRotator CurrentRotation = OwnerRef->GetActorRotation();
	FRotator TargetRotation =  UKismetMathLibrary::FindLookAtRotation(OwnerLocation, PlayerLocation);


	FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(CurrentRotation,TargetRotation, DeltaTime, RotateSpeed);

	FRotator NewYawOnlyRotation{CurrentRotation.Pitch,NewRotation.Yaw ,CurrentRotation.Roll };

	OwnerRef->SetActorRotation(NewYawOnlyRotation);

	// ...
}

