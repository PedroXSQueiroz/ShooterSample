// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierFactory.h"
#include <WarOfTerror/Public/Soldier.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

SoldierFactory::SoldierFactory()
{
}

SoldierFactory::~SoldierFactory()
{
}

ASoldier* SoldierFactory::BuildSoldier( UWorld* world, FString soldierId) 
{
	const FActorSpawnParameters newSoldierParams = FActorSpawnParameters();

	const FVector newSoldierPosition = FVector(0, 0, 0);
	const FRotator newSoldierRotation = FRotator(0, 0, 0);

	ASoldier* currentNewSoldier = world->SpawnActor<ASoldier>(
		newSoldierPosition
		, newSoldierRotation
		, newSoldierParams
	);

	UE_LOG(LogTemp, Log, TEXT("DEFAULT SOLDIER CREATED"));

	return currentNewSoldier;
}
