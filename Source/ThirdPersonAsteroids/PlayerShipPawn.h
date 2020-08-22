// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShipPawn.h"
#include "PlayerShipPawn.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UCameraShake;
UCLASS()
class THIRDPERSONASTEROIDS_API APlayerShipPawn : public ABaseShipPawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

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
	
	APlayerController* PlayerControllerRef;

	void CalculateMoveInput(float Value);
	void CalculateYawRotateInput(float Value);
	void CalculatePitchRotateInput(float Value);
	float CalculateAcceleration(float Value);
	FVector CreateMoveVector(float Value, FVector Speeds);
	void MomentumDisipation();
	float Disipate(float Value);
	virtual void Fire() override;

	void Move();
	void Rotate();
	//speed stuff
	FVector CurrentLocation = FVector(0.0f);
	FVector OldLocation = FVector(0.0f);


public:
	// Sets default values for this pawn's properties
	APlayerShipPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
