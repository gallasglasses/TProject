// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_MenuPlayerBoardWidget.h"

#include "Components/VerticalBox.h"
#include "Components/Button.h"

void UTP_MenuPlayerBoardWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UTP_MenuPlayerBoardWidget::OnStartGame);
	}
}

void UTP_MenuPlayerBoardWidget::UpdatePlayersStat()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	// take info from data
}

void UTP_MenuPlayerBoardWidget::OnStartGame()
{
}
