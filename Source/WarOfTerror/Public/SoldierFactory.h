// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class WAROFTERROR_API SoldierFactory
{
public:
	SoldierFactory();
	~SoldierFactory();

	static class ASoldier* BuildSoldier(UWorld* world, FString id);
};
