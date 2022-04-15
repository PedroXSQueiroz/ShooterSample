// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyShooterController.h"

#include "Soldier.h"
#include "ShooterController.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <WarOfTerror/Public/SoldierFactory.h>

// Sets default values
ADummyShooterController::ADummyShooterController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void ADummyShooterController::BeginPlay()
{
	Super::BeginPlay();

	this->SetSoldier(SoldierFactory::BuildSoldier(this->GetWorld(), FString("Default")));
	
	TArray<AActor*> shootersFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterController::StaticClass(), shootersFound);

	this->Target = Cast<AShooterController>( shootersFound[0] );

	this->RootComponent->SetWorldLocation(FVector(0, 0, 20));
	
}

// Called every frame
void ADummyShooterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = this->RootComponent->GetComponentLocation();

	this->PointOfView->X = currentLocation.X;
	this->PointOfView->Y = currentLocation.Y;
	this->PointOfView->Z = currentLocation.Z;

	FRotator headRotation = UKismetMathLibrary::FindLookAtRotation(this->RootComponent->GetComponentLocation(), this->Target->GetSoldierPosition());

	this->RotationOfView->Pitch = headRotation.Pitch;
	this->RotationOfView->Yaw = headRotation.Yaw;
	this->RotationOfView->Roll = headRotation.Roll;

	double distance = UKismetMathLibrary::Distance2D(
		FVector2D(this->PointOfView->X, this->PointOfView->Y),
		FVector2D(this->Target->GetSoldierPosition().X, this->Target->GetSoldierPosition().Y)
	);

	/*UE_LOG(LogTemp, Log, TEXT("`Distance from target %f"), distance);*/
	FRotator currentSoldierRotation = this->Soldier->GetRootComponent()->GetComponentRotation();

	if (distance < this->MinDistance) 
	{
		//this->Soldier->Move(0.5, headRotation.Yaw + 180);

		this->Soldier->Move(-0.5, FMath::DegreesToRadians( 90 ) );
		this->Soldier->Rotate(headRotation.Yaw - currentSoldierRotation.Yaw);
		//UE_LOG(LogTemp, Log, TEXT("`Less than min, Distance from target %f"), distance);
	}
	else if (distance < this->MaxDistance) 
	{
		//UE_LOG(LogTemp, Log, TEXT("`Between min and max, Distance from target %f"), distance);
		//this->Soldier->Move(0, 0);
		//this->Soldier->Rotate(headRotation.Yaw - currentSoldierRotation.Yaw);
	}
	else 
	{
		this->Soldier->Move(0.5, FMath::DegreesToRadians( 90 ) );
		this->Soldier->Rotate(headRotation.Yaw - currentSoldierRotation.Yaw);
		//UE_LOG(LogTemp, Log, TEXT("`More than max, Distance from target %f"), distance);
	}


}

void ADummyShooterController::SetSoldier(ASoldier* soldier) 
{
	this->Soldier = soldier;

	this->PointOfView = new FVector(0, 0, 0);
	this->RotationOfView = new FRotator(0, 0, 0);

	this->RootComponent = this->Soldier->GetRootComponent();
	this->Soldier->SetRayCastAimStart(this->PointOfView, this->RotationOfView);
}

