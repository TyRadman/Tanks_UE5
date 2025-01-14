// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector TargetLocation)
{
	FVector ToTargetVector = TargetLocation - TurretMesh->GetComponentLocation();
	FRotator LookRotation(0.f, ToTargetVector.Rotation().Yaw, 0.0f);

	float InterpolationSpeed = 25.f;
	
	FRotator NewRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		InterpolationSpeed);
	
	TurretMesh->SetWorldRotation(NewRotation);
}

void ABasePawn::Shoot()
{
	FVector ShootingPoint = ProjectileSpawnPoint->GetComponentLocation();
	DrawDebugSphere(GetWorld(), ShootingPoint, 20, 30, FColor::Red, false, 2.f);
}


