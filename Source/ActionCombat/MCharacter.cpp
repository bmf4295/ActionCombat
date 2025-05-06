// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "PlayerAnimInstance.h"
#include "StatsComponent.h"
#include "BlockComponent.h"
#include "LockOnComponent.h"
#include "CombatComponent.h"
#include "TraceComponent.h"
#include "PlayerActionsComponent.h"
#include "EStat.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	BlockComp = CreateDefaultSubobject<UBlockComponent>(TEXT("Block Component"));
	LockonComp = CreateDefaultSubobject<ULockOnComponent>(TEXT("Lockon Component"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace Component"));
	PlayerActionsComp = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("Player Actions Component"));

}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMCharacter::GetDamage(){
	return StatsComp->Stats[EStat::Strength];
}

bool AMCharacter::HasEnoughStamina(float StaminaCost){
	return StatsComp->Stats[EStat::Stamina] >= StaminaCost;
}

void AMCharacter::HandleDeath(){
	PlayAnimMontage(DeathAnimMontage);
	DisableInput(GetController<APlayerController>());
}

void AMCharacter::EndLockonWithActor(AActor* ActorRef){
	if(ActorRef != LockonComp->CurrentTargetActor){
		return;
	}
	LockonComp->EndLockon();
}

bool AMCharacter::CanTakeDamage(AActor* Opponent){
	if(PlayerActionsComp->bIsRollActive){
		return false;
	}

	if(PlayerAnim->bIsBlocking){
		return BlockComp->Check(Opponent);
	}
	return true;
}

void AMCharacter::PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate){
	PlayAnimMontage(HurtAnimMontage);
	
	if(CameraShakeTemplate){
		GetController<APlayerController>()->ClientStartCameraShake(CameraShakeTemplate);
	}
}