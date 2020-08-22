// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipPawn.h"
#include "GameFramework/SpringArmCOmponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"



void APlayerShipPawn::CalculateMoveInput(float Value)
{
	CurrentLocation = GetActorLocation();
	FVector Speeds = CurrentLocation-OldLocation;
	FVector OldMoveDirection = MoveDirection;
	FVector NewMoveInput = CreateMoveVector(Value, Speeds);
	OldLocation = CurrentLocation;
	//MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	FVector NewMoveDirection = NewMoveInput + OldMoveDirection;
	MoveDirection = FVector(NewMoveDirection);
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



float APlayerShipPawn::CalculateAcceleration(float Value)
{
	if (Value < 0.0f)
	{
		return((MaxSpeed - (MaxSpeed*2)) - Value) / (MaxSpeed-MaxSpeed*2);
	}
	else if(Value > 0.0f)
	{
		return ((MaxSpeed - Value) / MaxSpeed);
	}
	else
	{
		return 1.0f;
	}
}

FVector APlayerShipPawn::CreateMoveVector(float Value, FVector Speeds)
{
	FVector Speed = Speeds;
	FRotator ObjectRotation = GetActorRotation();
	FVector NewMoveInput = ObjectRotation.Vector();
	NewMoveInput.X = NewMoveInput.X * (Value * MoveSpeed * CalculateAcceleration(Speed.X)) * GetWorld()->DeltaTimeSeconds;
	NewMoveInput.Y = NewMoveInput.Y * (Value * MoveSpeed * CalculateAcceleration(Speed.Y)) * GetWorld()->DeltaTimeSeconds;
	NewMoveInput.Z = NewMoveInput.Z * (Value * MoveSpeed * CalculateAcceleration(Speed.Z)) * GetWorld()->DeltaTimeSeconds;
	return NewMoveInput;
}

void APlayerShipPawn::MomentumDisipation()
{
	UE_LOG(LogTemp, Warning, TEXT("input X %f"), MoveDirection.X);
	UE_LOG(LogTemp, Warning, TEXT("input Y %f"), MoveDirection.Y);
	UE_LOG(LogTemp, Warning, TEXT("input Z %f"), MoveDirection.Z);
	MoveDirection.X = Disipate(MoveDirection.X);
	MoveDirection.Y = Disipate(MoveDirection.Y);
	MoveDirection.Z = Disipate(MoveDirection.Z);
	UE_LOG(LogTemp, Warning, TEXT("Output X %f"), MoveDirection.X);
	UE_LOG(LogTemp, Warning, TEXT("Output Y %f"), MoveDirection.Y);
	UE_LOG(LogTemp, Warning, TEXT("Output Z %f"), MoveDirection.Z);

}

float APlayerShipPawn::Disipate(float Value)
{
	if (Value > 0)
	{
		return Value * ((100 - SlowDownRate)/100);
	}
	else if (Value < 0)
	{
		return Value * ((100 - SlowDownRate) / 100);
	}
	else
	{
		return Value;
	}
}

void APlayerShipPawn::Fire()
{
	Super::Fire();
}

void APlayerShipPawn::Move()
{
	AddActorWorldOffset(MoveDirection, true);
	//AddActorLocalOffset(MoveDirection, true);
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
	OldLocation = GetActorLocation();

}

// Called when the game starts or when spawned
void APlayerShipPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
	GetWorld()->GetTimerManager().SetTimer(SlowDownTimerHandle, this, &APlayerShipPawn::MomentumDisipation, SlowDownTime, true);
	
}

// Called to bind functionality to input
void APlayerShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//movement
	PlayerInputComponent->BindAxis("Thrust", this, &APlayerShipPawn::CalculateMoveInput);
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

