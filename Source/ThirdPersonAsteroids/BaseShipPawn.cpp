// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShipPawn.h"
#include "Components/CapsuleComponent.h"
#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
ABaseShipPawn::ABaseShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(BaseMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void ABaseShipPawn::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}

// Called when the game starts or when spawned
void ABaseShipPawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SlowDownTimerHandle, this, &ABaseShipPawn::MomentumDisipation, SlowDownTime, true);
	
}

void ABaseShipPawn::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

// Called every frame
void ABaseShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseShipPawn::CalculateMoveInput(float Value)
{
	CurrentLocation = GetActorLocation();
	FVector Speeds = CurrentLocation - OldLocation;
	FVector OldMoveDirection = MoveDirection;
	FVector NewMoveInput = CreateMoveVector(Value, Speeds);
	OldLocation = CurrentLocation;
	//MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	FVector NewMoveDirection = NewMoveInput + OldMoveDirection;
	MoveDirection = FVector(NewMoveDirection);
}

void ABaseShipPawn::CalculateYawRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirectionYaw = FQuat(Rotation);
}

void ABaseShipPawn::CalculatePitchRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(RotateAmount, 0, 0);
	RotationDirectionPitch = FQuat(Rotation);
}



float ABaseShipPawn::CalculateAcceleration(float Value)
{
	if (Value < 0.0f)
	{
		return((MaxSpeed - (MaxSpeed * 2)) - Value) / (MaxSpeed - MaxSpeed * 2);
	}
	else if (Value > 0.0f)
	{
		return ((MaxSpeed - Value) / MaxSpeed);
	}
	else
	{
		return 1.0f;
	}
}

FVector ABaseShipPawn::CreateMoveVector(float Value, FVector Speeds)
{
	FVector Speed = Speeds;
	FRotator ObjectRotation = GetActorRotation();
	FVector NewMoveInput = ObjectRotation.Vector();
	NewMoveInput.X = NewMoveInput.X * (Value * MoveSpeed * CalculateAcceleration(Speed.X)) * GetWorld()->DeltaTimeSeconds;
	NewMoveInput.Y = NewMoveInput.Y * (Value * MoveSpeed * CalculateAcceleration(Speed.Y)) * GetWorld()->DeltaTimeSeconds;
	NewMoveInput.Z = NewMoveInput.Z * (Value * MoveSpeed * CalculateAcceleration(Speed.Z)) * GetWorld()->DeltaTimeSeconds;
	return NewMoveInput;
}

void ABaseShipPawn::MomentumDisipation()
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

float ABaseShipPawn::Disipate(float Value)
{
	if (Value > 0)
	{
		return Value * ((100 - SlowDownRate) / 100);
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

void ABaseShipPawn::Move()
{
	AddActorWorldOffset(MoveDirection, true);
	//AddActorLocalOffset(MoveDirection, true);
}

void ABaseShipPawn::Rotate()
{
	AddActorLocalRotation(RotationDirectionYaw, true);
	AddActorLocalRotation(RotationDirectionPitch, true);
}