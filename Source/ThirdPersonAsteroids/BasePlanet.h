// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlanet.generated.h"
class USceneComponent;
class UDirectionalLightComponent;
class ABaseStar;
UCLASS()
class THIRDPERSONASTEROIDS_API ABasePlanet : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UDirectionalLightComponent* SunLight;
	UPROPERTY(EditAnywhere, Category = "Light", meta = (AllowPrivateAccess = "true"))
	ABaseStar* LocalStar;
public:	
	// Sets default values for this actor's properties
	ABasePlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
