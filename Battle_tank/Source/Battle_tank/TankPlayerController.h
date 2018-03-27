// Fill out your copyright notice in the Description page of Project Settings.

#pragma once








#include "public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank * GetControlledTank() const;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	//Move the barrel of the tank toward the intersecting between the worl ind the crosshaire
	void AimTowardCrossaihair();
	//cast a rayscan in the world through the UI and if it hit something will output an FVecor location of were it hit
	bool GetSightRayHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333;

	bool GetLookDirection(FVector2D ,FVector& ) const;
};
