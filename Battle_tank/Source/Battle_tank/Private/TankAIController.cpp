// Fill out your copyright notice in the Description page of Project Settings.

#include "public/TankAIController.h"
/*
At begin play make sure that it has all the element to function
*/
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

/*
Return the pawn as a tank
*/
ATank * ATankAIController::GetAIControlledTank() const
{	
	return Cast<ATank>(GetPawn());	
}

/*
find the player in the world and return it as a tank
*/
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
/*
At every tick will try to aim at player
*/
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
