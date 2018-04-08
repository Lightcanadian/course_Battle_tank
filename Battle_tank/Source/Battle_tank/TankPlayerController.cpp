// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

//Make a indicator for reference pointer
#define OUT

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
	
}

/*
*
*/
void ATankPlayerController::AimTowardCrossaihair()
{
	if (!GetControlledTank()){ return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		// UE_LOG(LogTemp, Warning, TEXT("Ray Location HIt: %s"), *HitLocation.ToString());
		//get world location if line trace through crosshaire
	}
}

/*
Get the location of the raycast out of camera reticule
*/
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
		GetLookVectorHitLocation(LookDirection, OUT OutHitLocation);
		return true;
	}
	
	return false;
}

/*
give the direction of where the camera is looking at. location is the reticule location in the UI.
*/
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
/*
Do a line trace out of the camera with the provided look direction
*/
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel( HitResult, StartLocation,	EndLocation, ECollisionChannel::ECC_Visibility)	)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0, 0, 0);
	return false;
}

ATank * ATankPlayerController::GetControlledTank() const
{
	//Transform the pawn into a tank
	return Cast<ATank>(GetPawn());
}