// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity(){
    APawn* OwnerPawn {TryGetPawnOwner()};

    if(!IsValid(OwnerPawn)){
        return;
    }
    FVector VelocityVec{ OwnerPawn->GetVelocity()};
    CurrentVelocity = static_cast<float>(VelocityVec.Length());
}