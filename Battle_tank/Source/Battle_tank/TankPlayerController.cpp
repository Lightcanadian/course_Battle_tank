// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayController not posessing tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller posessing %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrossaihair();
	//UE_LOG(LogTemp, Warning, TEXT("time: %f"), DeltaTime);
	//tick 
		//super
		//AimTowardCrossaire
}

void ATankPlayerController::AimTowardCrossaihair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		//get world location if line trace through crosshaire
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//find the Crosshaire location in pixel coordinate
	int32 ViewportSizeX, ViewportSizeY;
	FVector CameraWorldDirection, ignore;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ReticulLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ReticulLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *CameraWorldDirection.ToString());
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D Location,FVector &OutLookDirection) const
{	
	FVector ignore;
	//"De-project"the screen location of the crosshair
	return DeprojectScreenPositionToWorld(
		Location.X,
		Location.Y,
		ignore,
		OutLookDirection
	);
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}