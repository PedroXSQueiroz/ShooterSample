// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShooterController.generated.h"

UCLASS()
class WAROFTERROR_API AShooterController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShooterController();

	void SetSoldier(class ASoldier* soldier);

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="SHOOTER_CONTROLLER")
	class UCameraComponent* Camera;

	void SetWorldLocation(FVector position);
	
	void RotateSoldier(float);

	void PitchVision(float angle);

	void AddXMovement(float xMovement);

	void AddYMovement(float yMovement);

	void ToggleSoldierShoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SHOOTER_CONTROLLER")
	float MaxVisionPicth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SHOOTER_CONTROLLER")
	float MinVisionPitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ASoldier* Soldier;

	FVector MoveDirection;

	FVector* PointOfView;

	FRotator* RotationOfView;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	float GetVelocityFromMoveDirection();

};
