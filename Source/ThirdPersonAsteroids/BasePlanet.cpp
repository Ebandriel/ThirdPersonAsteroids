// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlanet.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DirectionalLightComponent.h"
// Sets default values
ABasePlanet::ABasePlanet()
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
void ABasePlanet::BeginPlay()
{
	Super::BeginPlay();
	// find sun
	
}

// Called every frame
void ABasePlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

