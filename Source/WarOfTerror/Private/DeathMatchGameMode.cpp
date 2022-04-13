// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathMatchGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "ShooterController.h"
#include "SoldierFactory.h"
#include "Soldier.h"

void ADeathMatchGameMode::BeginPlay() 
{
	Super::BeginPlay();
	
	ASoldier* currentPlayerSoldier = SoldierFactory::BuildSoldier(this->GetWorld(), FString("DEFAULT"));

	APawn* currentPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	this->Controller = Cast<AShooterController>(currentPlayerPawn);

	this->Controller->SetWorldLocation(FVector(0, 0, 20));
	
	this->Controller->SetSoldier(currentPlayerSoldier);
	
}
