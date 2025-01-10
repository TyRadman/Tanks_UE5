// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	UPROPERTY(VisibleDefaultsOnly)
	int32 valueValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UCapsuleComponent> CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tank Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
