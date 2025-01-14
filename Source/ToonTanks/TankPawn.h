// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPawn.generated.h"

/**
 * 
 */

UCLASS()
class TOONTANKS_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	ATankPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Tank Components")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Tank Components")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category="Tank Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category="Tank Input")
	TObjectPtr<class UInputAction> MovementInputAction;
	
	UPROPERTY(EditAnywhere, Category="Tank Input")
	TObjectPtr<UInputAction> TurnInputAction;
	
	UPROPERTY(EditAnywhere, Category="Tank Input")
	TObjectPtr<UInputAction> ShootInputAction;

	UPROPERTY(EditAnywhere, Category="Tank Stats")
	float MovementSpeed = 200.f;
	
	UPROPERTY(EditAnywhere, Category="Tank Stats")
	float TurnSpeed = 200.f;

	APlayerController* PlayerControllerRef;

	void Move(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);
	void PerformShooting(const struct FInputActionValue& Value);
};
