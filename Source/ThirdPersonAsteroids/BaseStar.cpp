// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStar.h"
#include "PlayerShipPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DirectionalLightComponent.h"

// Sets default values
ABaseStar::ABaseStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	SunLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Sun Light"));
	SunLight->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseStar::BeginPlay()
{
	Super::BeginPlay();
	PlayerShip = Cast<APlayerShipPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ABaseStar::RotateLightSource(FVector LookAtPlayer)
{
	FVector LookAtTargetClean = LookAtPlayer;
	FVector StartLocation = SunLight->GetComponentLocation();
	FRotator LightRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	SunLight->SetWorldRotation(LightRotation);
}

// Called every frame
void ABaseStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerShip == nullptr)
	{
		return;
	}
	RotateLightSource(PlayerShip->GetActorLocation());
}

