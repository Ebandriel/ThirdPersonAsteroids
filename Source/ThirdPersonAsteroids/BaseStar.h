// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseStar.generated.h"
class USceneComponent;
class UDirectionalLightComponent;
class APlayerShipPawn;
UCLASS()
class THIRDPERSONASTEROIDS_API ABaseStar : public AActor
{
	GENERATED_BODY()
private:
	//components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UDirectionalLightComponent* SunLight;

	APlayerShipPawn* PlayerShip;
 
public:	
	// Sets default values for this actor's properties
	ABaseStar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateLightSource(FVector LookAtPlayer);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
