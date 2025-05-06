// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::ReduceHealth(float Damage){
	
	if(Stats[EStat::Health] <= 0){return;}

	Stats[EStat::Health] = Stats[EStat::Health]-Damage;
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(Stats[EStat::Health], 0.0,Stats[EStat::MaxHealth]);
	OnHealthPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Health, EStat::MaxHealth));

	if(Stats[EStat::Health] == 0.0){
		OnZeroHealthDelegate.Broadcast();
	}
}

void UStatsComponent::ReduceStamina(float Amount){

	Stats[EStat::Stamina]  = Stats[EStat::Stamina] -Amount;
	Stats[EStat::Stamina] = UKismetMathLibrary::FClamp(Stats[EStat::Stamina], 0.0,Stats[EStat::MaxStamina]);
	bCanRegen = false;
	FLatentActionInfo FuntionInfo{
		0,
		100,
		TEXT("EnableRegen"),
		this
	};
	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Stamina,EStat::MaxStamina ));
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(),StaminaDelayDuration, FuntionInfo );
}
void UStatsComponent::RegenStamina(){
	if(!bCanRegen){return;}
	Stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina],
		Stats[EStat::MaxStamina], 
		GetWorld()->GetDeltaSeconds(),
		StaminaRegenRate
	);

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Stamina,EStat::MaxStamina ));
}

void UStatsComponent::EnableRegen(){
	bCanRegen = true;
}

float UStatsComponent::GetStatPercentage(EStat Current, EStat Max){
	return Stats[Current]/ Stats[Max];
}