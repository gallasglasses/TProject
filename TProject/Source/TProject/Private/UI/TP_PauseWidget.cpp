// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TP_PauseWidget.h"
#include "Components/Button.h"
#include "Gameframework/GameModeBase.h"
#include "GameCore/TP_GameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPauseWidget, All, All);

void UTP_PauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UTP_PauseWidget::OnContinue);
	}
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UTP_PauseWidget::OnRestart);
	}
	if (BackToMenuButton)
	{
		BackToMenuButton->OnClicked.AddDynamic(this, &UTP_PauseWidget::OnBackToMenu);
	}
}

void UTP_PauseWidget::OnContinue()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UTP_PauseWidget::OnRestart()
{
	const auto TPGameInstance = GetTPGameInstance();
	if (!TPGameInstance) return;

	UE_LOG(LogPauseWidget, Display, TEXT("************** OnRestart *************"));
	UGameplayStatics::OpenLevel(this, TPGameInstance->GetGameLevelName());
}

void UTP_PauseWidget::OnBackToMenu()
{
	const auto TPGameInstance = GetTPGameInstance();
	if (!TPGameInstance) return;

	UE_LOG(LogPauseWidget, Display, TEXT("************** OnBackToMenu *************"));
	UGameplayStatics::OpenLevel(this, TPGameInstance->GetMenuLevelName());
}

UTP_GameInstance* UTP_PauseWidget::GetTPGameInstance() const
{
	if (!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<UTP_GameInstance>();
}