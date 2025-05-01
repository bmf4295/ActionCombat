// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateSpeed()
{
    APawn *OwnerPawn{TryGetPawnOwner()};

    if (!IsValid(OwnerPawn))
    {
        return;
    }
    FVector VelocityVec{OwnerPawn->GetVelocity()};
    CurrentSpeed = static_cast<float>(VelocityVec.Length());
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor *NewActor)
{
    bIsInCombat = IsValid(NewActor);

}

void  UPlayerAnimInstance::UpdateDirection(){
    APawn* PawnRef = TryGetPawnOwner();
    if(!IsValid(PawnRef)){return;}
    if(!bIsInCombat){return;}

    CurrentDirection = CalculateDirection(PawnRef->GetVelocity(), PawnRef->GetActorRotation());
}