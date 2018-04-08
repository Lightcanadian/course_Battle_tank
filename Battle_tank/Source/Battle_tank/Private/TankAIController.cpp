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

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *(PlayerTank->GetName()));
	}

}

ATank * ATankAIController::GetAIControlledTank() const
{	
	return Cast<ATank>(GetPawn());	
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerTank);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO move toward player
		//aim toward player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//fire when ready
	}
}
