// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TP_GameOverWidget.h"
#include "GameCore/TP_GameInstance.h"
#include "GameCore/TP_PlayerState.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameOverWidget, All, All);

int32 UTP_GameOverWidget::GetScore() const
{
    if (!GetTPPlayerState()) return 0;

    return GetTPPlayerState()->GetScore();
}

void UTP_GameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UTP_GameOverWidget::OnMatchStateChanged);
        }
    }

    if (RestartGameButton)
    {
        RestartGameButton->OnClicked.AddDynamic(this, &UTP_GameOverWidget::OnRestartGame);
    }

    if (BackToMenuButton)
    {
        BackToMenuButton->OnClicked.AddDynamic(this, &UTP_GameOverWidget::OnBackToMenu);
    }
}

void UTP_GameOverWidget::OnMatchStateChanged(ETPMatchState NewState)
{
    if (NewState == ETPMatchState::GameOver)
    {
        //UpdatePlayersStat();
    }
}

void UTP_GameOverWidget::OnRestartGame()
{
    const auto TPGameInstance = GetTPGameInstance();
    if (!TPGameInstance) return;

    if (!GetTPPlayerState()) return;
    GetTPPlayerState()->AddPlayCount();

    if (GetScore() > GetTPPlayerState()->GetMaxScore())
    {
        GetTPPlayerState()->SetMaxScore(GetScore());
    }
    
    UE_LOG(LogGameOverWidget, Display, TEXT("MaxScore : %i"), GetTPPlayerState()->GetMaxScore());
    UE_LOG(LogGameOverWidget, Display, TEXT("PlayCount : %i"), GetTPPlayerState()->GetPlayCount());

    UE_LOG(LogGameOverWidget, Display, TEXT("************** OnRestart *************"));
    UGameplayStatics::OpenLevel(this, TPGameInstance->GetGameLevelName());
}

void UTP_GameOverWidget::OnBackToMenu()
{
    const auto TPGameInstance = GetTPGameInstance();
    if (!TPGameInstance) return;

    UE_LOG(LogGameOverWidget, Display, TEXT("************** OnBackToMenu *************"));
    UGameplayStatics::OpenLevel(this, TPGameInstance->GetMenuLevelName());
}

UTP_GameInstance* UTP_GameOverWidget::GetTPGameInstance() const
{
    if (!GetWorld()) return nullptr;

    return GetWorld()->GetGameInstance<UTP_GameInstance>();
}

ATP_PlayerState* UTP_GameOverWidget::GetTPPlayerState() const
{
    if (!GetWorld()) return nullptr;

    const auto PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return nullptr;

    const auto TPPlayerState = Cast<ATP_PlayerState>(PC->PlayerState);
    if (!TPPlayerState) return nullptr;

    return TPPlayerState;
}
