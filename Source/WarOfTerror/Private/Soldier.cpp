// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"

#include "Components/CapsuleComponent.h"

#include "ShooterController.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>




// Sets default values
ASoldier::ASoldier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("SOLDIER_PHYSICS"));
	
	this->CollisionCapsule->InitCapsuleSize(10, 20);
	this->CollisionCapsule->SetEnableGravity(true);
	this->CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	this->RootComponent = this->CollisionCapsule;

	this->Movement = FVector(0, 0, 0);
	this->Rotation = FRotator(0, 0, 0);

	
	this->AimHitSign = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIM_SIGN"));
	this->AimHitSign->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereMeshAsset.Succeeded()) 
	{
		this->AimHitSign->SetStaticMesh(SphereMeshAsset.Object);
		this->AimHitSign->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->AimHitSign->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
	}
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoldier::Tick(float DeltaTime)
{
	FHitResult* hitResult = NULL;

	if (this->CollisionCapsule != NULL)
	{
		//UE_LOG(LogTemp, Log, TEXT("SOLDIER UPDATE INVOKED, ROTATION Z %f, VELOCITY: %f"), this->rotation.Euler().Z, FMath::Abs(this->movement.X) + FMath::Abs( this->movement.Y ) );
		
		FTransform currentTransformDelta = FTransform();
		
		currentTransformDelta.SetTranslation(this->Movement);
		currentTransformDelta.SetRotation(this->Rotation.Quaternion());

		this->CollisionCapsule->AddLocalTransform(currentTransformDelta);
	}

	this->UpdateAimTarget();

	this->AimHitSign->SetWorldLocation(*this->GetAimTarget());
}

USceneComponent* ASoldier::GetRootComponent() 
{
	return this->RootComponent;
}

void ASoldier::Move(float velocity, float angle) 
{
	
	float xVelocityNormalized = FMath::Sin(angle);
	float yVelocityNormalized = FMath::Cos(angle);

	//UE_LOG(LogTemp, Log, TEXT("Movement, x:%f y:%f"), xVelocityNormalized, yVelocityNormalized);

	this->Movement = FVector(xVelocityNormalized, yVelocityNormalized, 0) * velocity;
	
}

void ASoldier::Rotate(float angle) 
{
	this->Rotation = FRotator( 0, angle, 0 ) ;
}

void ASoldier::ToggleShoot() 
{
	this->IsShooting = !this->IsShooting;

	if (this->IsShooting) 
	{
		UE_LOG(LogTemp, Log, TEXT("Startted shooting"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Stopped shooting"));
	}
}

void ASoldier::SetRayCastAimStart(FVector* position, FRotator* rotation) 
{
	this->AimRayCastStartPosition = position;
	this->AimRayCastStartRotation = rotation;
}

FVector* ASoldier::GetAimTarget() 
{
	if (!this->AimRayCastStartPosition || !this->AimRayCastStartRotation)
	{
		return NULL;
	}
	
	this->UpdateAimTarget();
	return this->AimTarget;

}

void ASoldier::UpdateAimTarget() 
{
	
	if (!this->AimRayCastStartPosition || !this->AimRayCastStartRotation) 
	{
		return;
	}
	
	FHitResult hit;

	FVector start = *this->AimRayCastStartPosition;
	FVector end = start + (UKismetMathLibrary::GetForwardVector( *this->AimRayCastStartRotation ) * 1000);


	this->GetWorld()->LineTraceSingleByChannel(
		hit,
		start,
		end,
		ECC_MAX,
		FCollisionQueryParams(),
		FCollisionResponseParams()
	);

	if (!this->AimTarget)
	{
		this->AimTarget = new FVector(0, 0, 0);
	}

	if (hit.GetActor())
	{
		this->AimTarget->X = hit.Location.X;
		this->AimTarget->Y = hit.Location.Y;
		this->AimTarget->Z = hit.Location.Z;
	}
	else
	{
		this->AimTarget->X = end.X;
		this->AimTarget->Y = end.Y;
		this->AimTarget->Z = end.Z;
	}
}