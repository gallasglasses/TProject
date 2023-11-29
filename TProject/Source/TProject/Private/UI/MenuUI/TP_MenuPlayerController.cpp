// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_MenuPlayerController.h"

void ATP_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
