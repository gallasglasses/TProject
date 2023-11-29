// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TP_GameInstance.generated.h"

UCLASS()
class TPROJECT_API UTP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FName GetMenuLevelName() const { return MenuLevelName; }
	FName GetGameLevelName() const { return GameLevelName; }

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FName MenuLevelName;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		FName GameLevelName;
	
};
