// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"

void UBossAnimInstance::UpdateSpeed(){
    APawn *OwnerPawn{TryGetPawnOwner()};

    if (!IsValid(OwnerPawn))
    {
        return;
    }
    FVector VelocityVec{OwnerPawn->GetVelocity()};
    CurrentSpeed = static_cast<float>(VelocityVec.Length());
}