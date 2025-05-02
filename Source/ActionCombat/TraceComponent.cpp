// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CollisionShape.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Fighter.h"
#include "Engine/DamageEvents.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!bIsAttacking){return;}
	
	FVector StartSocketLocation = SkeletalComp->GetSocketLocation(Start);
	FVector EndSocketLocation = SkeletalComp->GetSocketLocation(End);
	FQuat ShapeRotation = SkeletalComp->GetSocketQuaternion(Rotation);
	
	double HalfBox = FVector::Dist(StartSocketLocation, EndSocketLocation);
	FVector BoxHalfExtent{BoxHeight,BoxWidth, HalfBox};
	BoxHalfExtent /=2;
	FCollisionShape Box = FCollisionShape::MakeBox(BoxHalfExtent);

	FCollisionQueryParams IgnoreParams{
		FName{TEXT("Ignore Params")},
		false,
		GetOwner()
	};
	TArray<FHitResult> OutResults;

	bool bHasFoundTarget = GetWorld()->SweepMultiByChannel(OutResults, StartSocketLocation, EndSocketLocation, ShapeRotation, ECollisionChannel::ECC_GameTraceChannel1, Box,IgnoreParams);
	
	if(bDebugMode){
		FLinearColor BoxColor;
		FVector CenterPoint = UKismetMathLibrary::VLerp(StartSocketLocation, EndSocketLocation, 0.5f);
		bHasFoundTarget? BoxColor = FLinearColor::Green: BoxColor = FLinearColor::Red;
		
		UKismetSystemLibrary::DrawDebugBox(GetWorld(),CenterPoint, Box.GetExtent(), BoxColor, ShapeRotation.Rotator(),1.0f,2.0f );
	}

	if(OutResults.Num() == 0){
		return;
	}
	float CharacterDamage =0.0f;
	IFighter* FighterRef = Cast<IFighter>(GetOwner());
	FDamageEvent TargetAttackEvent;
	if(FighterRef){
		CharacterDamage = FighterRef->GetDamage();
	}
	for(const FHitResult& Hit: OutResults){
		AActor* TargetActor = Hit.GetActor();
		if(TargetToIgnore.Contains(TargetActor)){
			continue;
		}
		TargetActor->TakeDamage(CharacterDamage, TargetAttackEvent, GetOwner()->GetInstigatorController(), GetOwner());
		TargetToIgnore.AddUnique(TargetActor);
	}
}

void UTraceComponent::HandleResetAttack(){
	TargetToIgnore.Empty();
}