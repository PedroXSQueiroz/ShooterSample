// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterController.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Soldier.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
AShooterController::AShooterController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>(FName("PLAYER_VISION"));

}

// Called when the game starts or when spawned
void AShooterController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShooterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector pointOfView;
	FRotator rotationOfView;

	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT pointOfView,
		OUT rotationOfView
	);

	this->PointOfView->X = pointOfView.X;
	this->PointOfView->Y = pointOfView.Y;
	this->PointOfView->Z = pointOfView.Z;

	this->RotationOfView->Pitch = rotationOfView.Pitch;
	this->RotationOfView->Roll = rotationOfView.Roll;
	this->RotationOfView->Yaw = rotationOfView.Yaw;

}

// Called to bind functionality to input
void AShooterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AShooterController::RotateSoldier);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AShooterController::PitchVision);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AShooterController::AddXMovement);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AShooterController::AddYMovement);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AShooterController::ToggleSoldierShoot);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &AShooterController::ToggleSoldierShoot);
	
}

void AShooterController::SetSoldier(ASoldier* currentSoldier) 
{
	this->Soldier = currentSoldier;

	this->Soldier->CollisionCapsule->SetWorldLocation(this->RootComponent->GetComponentLocation());
	this->RootComponent = this->Soldier->GetRootComponent();
	this->Camera->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	this->Camera->SetActive(true);

	this->PointOfView = new FVector(0, 0, 0);
	this->RotationOfView = new FRotator(0, 0, 0);

	this->Soldier->SetRayCastAimStart(this->PointOfView, this->RotationOfView);

}

void AShooterController::SetWorldLocation(FVector position) 
{
	this->RootComponent->SetWorldLocation(position);
}

void AShooterController::RotateSoldier(float angle)
{
	this->Soldier->Rotate(angle);
}

void AShooterController::PitchVision(float angle) 
{
	float currentPitch = this->Camera->GetComponentTransform().Rotator().Pitch;
	float updatedPitch = currentPitch + ( angle * -1 );

	if (	this->MinVisionPitch < updatedPitch 
		&&	updatedPitch < this->MaxVisionPicth)
	{
		this->Camera->AddRelativeRotation(FRotator(angle * -1, 0, 0), true);
	}
}

void AShooterController::AddXMovement(float xMovement) 
{
	this->MoveDirection.X = xMovement  ;

	this->Soldier->Move( this->GetVelocityFromMoveDirection() , FMath::Atan2( this->MoveDirection.X, this->MoveDirection.Y) );
}

void AShooterController::AddYMovement(float yMovement)
{
	this->MoveDirection.Y = yMovement;

	this->Soldier->Move( this->GetVelocityFromMoveDirection() , FMath::Atan2( this->MoveDirection.X, this->MoveDirection.Y ) );
}

float AShooterController::GetVelocityFromMoveDirection()
{
	
	float partialSin = this->MoveDirection.X / ( FMath::Abs( this->MoveDirection.X ) + FMath::Abs( this->MoveDirection.Y ) );
	float partialCos = this->MoveDirection.Y / ( FMath::Abs( this->MoveDirection.X ) + FMath::Abs( this->MoveDirection.Y ) );

	return UKismetMathLibrary::Hypotenuse(partialSin, partialCos);
}

void AShooterController::ToggleSoldierShoot() 
{
	this->Soldier->ToggleShoot();
}