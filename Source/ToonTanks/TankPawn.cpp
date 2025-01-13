// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"


ATankPawn::ATankPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	// connect the Input Mapping context to the player
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

			if (Subsystem)
			{
				// the index should be the index of the InputAction referenced in the InputMappingContext
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		
		PlayerControllerRef->GetHitResultUnderCursor(
			ECC_Visibility,
			false,
			HitResult);
		
		FVector HitPointLocation = HitResult.ImpactPoint;
		float Radius = 10.f;
		
		DrawDebugSphere(GetWorld(), HitPointLocation, Radius, 32, FColor::Red);

		RotateTurret(HitPointLocation);
	}

}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// set up the forward and backward movement input
		EnhancedInputComponent->BindAction(MovementInputAction, ETriggerEvent::Triggered, this, &ATankPawn::Move);

		// set up the left and right turn
		EnhancedInputComponent->BindAction(TurnInputAction, ETriggerEvent::Triggered, this, &ATankPawn::Turn);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The enhanced input component is null or not of type UEnhancedInputComponent"));
	}
}


void ATankPawn::Move(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();
	// GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Input is %f"), MovementValue));

	FVector DeltaLocation = FVector::ForwardVector * MovementValue * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	
	AddActorLocalOffset(DeltaLocation, true);
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	float RotationValue = Value.Get<float>();

	FRotator Rotation = FRotator::ZeroRotator;

	Rotation.Yaw = RotationValue * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	
	AddActorLocalRotation(Rotation, true);
}

