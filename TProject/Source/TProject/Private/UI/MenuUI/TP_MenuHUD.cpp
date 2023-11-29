// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_MenuHUD.h"
#include "UI/MenuUI/TP_MainMenuWidget.h"

void ATP_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		const auto MainMenuWidget = CreateWidget<UTP_MainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}

