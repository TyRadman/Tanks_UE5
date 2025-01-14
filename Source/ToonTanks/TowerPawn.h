// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TowerPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATowerPawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AggroRange = 5000.f;
	
	TObjectPtr<ABasePawn> TargetReference;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool IsTargetInRange() const;
};
