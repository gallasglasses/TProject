// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TP_MenuHUD.generated.h"

class UTP_MainMenuWidget;

UCLASS()
class TPROJECT_API ATP_MenuHUD : public AHUD
{
	GENERATED_BODY()

protected: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UTP_MainMenuWidget> MainMenuWidgetClass;

	virtual void BeginPlay() override;
	
};
