// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseShipPawn.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class USoundBase;
UCLASS()
class THIRDPERSONASTEROIDS_API ABaseShipPawn : public APawn
{
	GENERATED_BODY()
private:
	//components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UCameraShake> DeathShake;

	//movement components
	FTimerHandle SlowDownTimerHandle;
	FVector MoveDirection;
	FQuat RotationDirectionYaw;
	FQuat RotationDirectionPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float SlowDownRate = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float SlowDownTime = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MaxSpeed = 1000.0f;



public:
	// Sets default values for this pawn's properties
	ABaseShipPawn();

	virtual void HandleDestruction();

protected:

	float CalculateAcceleration(float Value);
	FVector CreateMoveVector(float Value, FVector Speeds);
	void MomentumDisipation();
	float Disipate(float Value);
	void Move();
	void Rotate();
	virtual void Fire();
	FVector CurrentLocation = FVector(0.0f);
	FVector OldLocation = FVector(0.0f);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CalculateMoveInput(float Value);
	void CalculateYawRotateInput(float Value);
	void CalculatePitchRotateInput(float Value);
	
};
