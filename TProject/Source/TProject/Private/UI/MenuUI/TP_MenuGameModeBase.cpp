// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_MenuGameModeBase.h"
#include "UI/MenuUI/TP_MenuHUD.h"
#include "UI/MenuUI/TP_MenuPlayerController.h"

ATP_MenuGameModeBase::ATP_MenuGameModeBase()
{
	PlayerControllerClass = ATP_MenuPlayerController::StaticClass();
	HUDClass = ATP_MenuHUD::StaticClass();
}