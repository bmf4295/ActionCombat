// Fill out your copyright notice in the Description page of Project Settings.

#include "LockOnComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
}

// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!IsValid(CurrentTargetActor)){
		return;	
	}
	FVector PlayerLocation = OwnerRef->GetActorLocation();
	FVector EnemyLocation = CurrentTargetActor->GetActorLocation();
	double TargetDistance = FVector::Distance(PlayerLocation,EnemyLocation);
	if( TargetDistance>= BreakDistance){
		EndLockon();
		return;
	}
	EnemyLocation.Z -=125;
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, EnemyLocation);
	Controller->SetControlRotation(TargetRotation);
	// ...
}

void ULockOnComponent::StartLockon(float Radius)
{

	FHitResult OutResult;
	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams IgnoreParameters{
		FName{TEXT("Ignore Collision Params")},
		false,
		OwnerRef
	};
	bool bHit = GetWorld()->SweepSingleByChannel(OutResult, CurrentLocation, CurrentLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, Sphere, IgnoreParameters);
	
	if(!bHit){
		return;
	}

	if(!OutResult.GetActor()->Implements<UEnemy>()){
		return;
	}
	
	CurrentTargetActor = OutResult.GetActor();
	Controller->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;

	SpringArmComp->TargetOffset= FVector{0.f,0.f,100.f};

	IEnemy::Execute_OnSelect(CurrentTargetActor);
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockOnComponent::EndLockon(){
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	
	CurrentTargetActor= nullptr;
	Controller->ResetIgnoreLookInput();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;
	SpringArmComp->TargetOffset = FVector::Zero();
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockOnComponent::ToggleLockon(float Radius){
	if(IsValid(CurrentTargetActor)){
		EndLockon();
	}else{
		StartLockon(Radius);
	}
}