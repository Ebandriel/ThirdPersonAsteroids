// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipPawn.h"
#include "GameFramework/SpringArmCOmponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"


void APlayerShipPawn::CalculateMoveInput(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Thrust %f"), Value);
	float SlowDown = 0.0f;
	float MaxSpeed = 100.0f;
	//old ship velocity x/y/z
	CurrentLocation = GetActorLocation();
	FVector Speeds = CurrentLocation-OldLocation;
	FVector OldMoveDirection = MoveDirection;
	//get new direction
	FRotator ObjectRotation = GetActorRotation();
	FVector NewMoveInput = ObjectRotation.Vector();
	//split to x/y/z
	
	float XThrust = NewMoveInput.X * (Value * MoveSpeed * ((MaxSpeed - Speeds.X) / MaxSpeed)) * GetWorld()->DeltaTimeSeconds;
	float YThrust = NewMoveInput.Y * (Value * MoveSpeed * ((MaxSpeed - Speeds.Y) / MaxSpeed)) * GetWorld()->DeltaTimeSeconds;
	float ZThrust = NewMoveInput.Z * (Value * MoveSpeed * ((MaxSpeed - Speeds.Z) / MaxSpeed)) * GetWorld()->DeltaTimeSeconds;

	UE_LOG(LogTemp, Warning, TEXT("Input Y %f"), NewMoveInput.X);
	UE_LOG(LogTemp, Warning, TEXT("Input Y %f"), NewMoveInput.Y);
	UE_LOG(LogTemp, Warning, TEXT("Input Y %f"), NewMoveInput.Z);
	UE_LOG(LogTemp, Warning,TEXT("X %f"), XThrust);
	UE_LOG(LogTemp, Warning,TEXT("Y %f"), YThrust);
	UE_LOG(LogTemp, Warning,TEXT("Z %f"), ZThrust);
	UE_LOG(LogTemp, Warning, TEXT("speed X %f"), Speeds.X);
	UE_LOG(LogTemp, Warning, TEXT("speed Y %f"), Speeds.Y);
	UE_LOG(LogTemp, Warning, TEXT("speed Z %f"), Speeds.Z);
	NewMoveInput.X = XThrust;
	NewMoveInput.Y = YThrust;
	NewMoveInput.Z = ZThrust;
	OldLocation = CurrentLocation;
	//get thrust
	//float Thrust = (Value * MoveSpeed *((MaxSpeed - CurrentSpeed) / MaxSpeed)) + CurrentSpeed - SlowDown;
	//apply speed to individual vector current speed/max speed/specific impulse
	//apply new velocities to old velocities
	//apply slowdown to each vector
	//new ship velocity x/y/z becomes move direction
	//MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	FVector NewMoveDirection = NewMoveInput + OldMoveDirection;
	//calculate slowdown on all vectors
	//final product in ne movement vector
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

	OldLocation = GetActorLocation();

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

