// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipPawn.h"
#include "GameFramework/SpringArmCOmponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"

void APlayerShipPawn::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APlayerShipPawn::CalculateRoatateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APlayerShipPawn::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APlayerShipPawn::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

// Sets default values
APlayerShipPawn::APlayerShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void APlayerShipPawn::BeginPlay()
{
	Super::BeginPlay();


	PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called to bind functionality to input
void APlayerShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APlayerShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerShipPawn::HandleDestruction()
{

}

