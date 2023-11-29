// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "GameCore/TP_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuWidget, All, All);

void UTP_MainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UTP_MainMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UTP_MainMenuWidget::OnQuitGame);
	}

}

void UTP_MainMenuWidget::OnStartGame()
{
	const auto TPGameInstance = GetTPGameInstance();
	if (!TPGameInstance) return;

	UE_LOG(LogMainMenuWidget, Display, TEXT("************** OnStartGame *************"));
	UGameplayStatics::OpenLevel(this, TPGameInstance->GetGameLevelName());
}

void UTP_MainMenuWidget::OnQuitGame()
{
	UE_LOG(LogMainMenuWidget, Display, TEXT("************** OnQuitGame *************"));
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

UTP_GameInstance* UTP_MainMenuWidget::GetTPGameInstance() const
{
	if (!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<UTP_GameInstance>();
}