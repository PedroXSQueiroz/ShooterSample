// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyShooterController.generated.h"


UCLASS()
class WAROFTERROR_API ADummyShooterController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyShooterController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DUMMY_SOLDIER")
	class ASoldier* Soldier;

	void SetSoldier(class ASoldier* soldier);

	FVector* PointOfView;

	FRotator* RotationOfView;

	class AShooterController* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DUMMY_SOLDIER")
	float MinDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DUMMY_SOLDIER")
	float MaxDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
