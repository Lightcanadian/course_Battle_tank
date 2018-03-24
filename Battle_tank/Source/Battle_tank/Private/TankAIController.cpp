// Fill out your copyright notice in the Description page of Project Settings.

#include "public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetAIControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not posessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller posessing %s"), *(ControlledTank->GetName()));
	}
}

ATank * ATankAIController::GetAIControlledTank() const
{	
	return Cast<ATank>(GetPawn());	
}
