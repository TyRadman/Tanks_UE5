// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerPawn.h"

#include "Kismet/GameplayStatics.h"

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	TargetReference = Cast<ABasePawn>(playerPawn);

	FTimerManager& TimerManager = GetWorldTimerManager();
	TimerManager.SetTimer(FireRateTimerHandle, this, &ATowerPawn::CheckFireCondition, FireRate, true);
}


void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TargetReference)
	{
		if (IsTargetInRange())
		{
			RotateTurret(TargetReference->GetActorLocation());
			// DrawDebugSphere(GetWorld(), GetActorLocation(), AggroRange, 30, FColor::Red);
		}
		else
		{
			FVector ForwardLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
			RotateTurret(ForwardLocation);
			// DrawDebugSphere(GetWorld(), GetActorLocation(), AggroRange, 30, FColor::Green);
		}
	}
}

bool ATowerPawn::IsTargetInRange() const
{
	if (!TargetReference)
	{
		return false;
	}
	
	float Distance = FVector::Dist(GetActorLocation(), TargetReference->GetActorLocation());
	
	return Distance <= AggroRange;
}

void ATowerPawn::CheckFireCondition()
{
	if(IsTargetInRange())
	{
		Shoot();
	}
}


