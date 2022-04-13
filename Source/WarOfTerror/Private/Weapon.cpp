// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Soldier.h"
//#include "Components/SphereComponent.h"

//USphereComponent* AimHitSign;

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	const FActorSpawnParameters newSoldierParams = FActorSpawnParameters();
	
	//AimHitSign = this->CreateDefaultSubobject<USphereComponent>(TEXT("AIM_SIGN"));
	//AimHitSign->InitSphereRadius(10);

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//AimHitSign->SetWorldLocation(*this->GetTarget());

}

void AWeapon::TakenBy(ASoldier* soldier) 
{
	this->CurrentOwner = soldier;
}

void AWeapon::ToggleIsLookinAtTarget() 
{
	this->IsLookingAtTarget = !this->IsLookingAtTarget;
}

void AWeapon::LookAtTarget() 
{

}

FVector* AWeapon::GetTarget() 
{
	return this->CurrentOwner->GetAimTarget();
}