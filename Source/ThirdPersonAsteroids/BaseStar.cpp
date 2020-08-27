// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStar.h"

// Sets default values
ABaseStar::ABaseStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	SunLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Sun Light"));
	SunLight->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseStar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

