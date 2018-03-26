// Fill out your copyright notice in the Description page of Project Settings.

#pragma once









#include "Engine/World.h"
#include "public/Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	ATank * GetAIControlledTank() const;
	ATank* GetPlayerTank() const;
};
