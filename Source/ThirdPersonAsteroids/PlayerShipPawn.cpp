// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipPawn.h"
#include "GameFramework/SpringArmCOmponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"


void APlayerShipPawn::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APlayerShipPawn::CalculateYawRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirectionYaw = FQuat(Rotation);
}

void APlayerShipPawn::CalculatePitchRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(RotateAmount, 0, 0);
	RotationDirectionPitch = FQuat(Rotation);
}



void APlayerShipPawn::Fire()
{
	Super::Fire();
}

void APlayerShipPawn::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APlayerShipPawn::Rotate()
{
	AddActorLocalRotation(RotationDirectionYaw, true);
	AddActorLocalRotation(RotationDirectionPitch, true);
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
	//movement

	//rotation
	PlayerInputComponent->BindAxis("Pitch", this, &APlayerShipPawn::CalculatePitchRotateInput);
	PlayerInputComponent->BindAxis("Yaw", this, &APlayerShipPawn::CalculateYawRotateInput);
	//action
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShipPawn::Fire);

}


void APlayerShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();
	
}

void APlayerShipPawn::HandleDestruction()
{

}

