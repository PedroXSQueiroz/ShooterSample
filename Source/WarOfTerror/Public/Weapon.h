// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class WAROFTERROR_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	void TakenBy(class ASoldier*);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ASoldier* CurrentOwner;

	void LookAtTarget();

	void ToggleIsLookinAtTarget();

	//FIXME: SHOULD BE VIRTUAL
	FVector* GetTarget();

	bool IsLookingAtTarget;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
