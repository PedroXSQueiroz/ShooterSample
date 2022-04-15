// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Soldier.generated.h"

UCLASS()
class WAROFTERROR_API ASoldier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldier();

	void Move(float, float);

	void Rotate(float);

	class USceneComponent* GetRootComponent();

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "SOLDIER_PHYSICS")
	class UCapsuleComponent* CollisionCapsule;

	void ToggleShoot();

	void SetRayCastAimStart(FVector*, FRotator*);

	FVector* GetAimTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOLDIER_DEBUG")
	UStaticMeshComponent* AimHitSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOLDIER_DEBUG")
	UStaticMeshComponent* SoldierBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SOLDIER_DEBUG")
	UStaticMeshComponent* SoldierHead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Movement;
	
	FRotator Rotation;

	FVector* AimRayCastStartPosition;

	FRotator* AimRayCastStartRotation;

	FVector* AimTarget;

	void UpdateAimTarget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool IsShooting;



};
