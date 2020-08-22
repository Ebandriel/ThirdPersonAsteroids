// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipPawn.h"
#include "GameFramework/SpringArmCOmponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"





void APlayerShipPawn::Fire()
{
	Super::Fire();
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
	PlayerInputComponent->BindAxis("Thrust", this, &ABaseShipPawn::CalculateMoveInput);
	//rotation
	PlayerInputComponent->BindAxis("Pitch", this, &ABaseShipPawn::CalculatePitchRotateInput);
	PlayerInputComponent->BindAxis("Yaw", this, &ABaseShipPawn::CalculateYawRotateInput);
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

