// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TProjectGameModeBase.h"
#include "TP_GameOverWidget.generated.h"


class UButton;
class UTP_GameInstance;
class ATP_PlayerState;

UCLASS()
class TPROJECT_API UTP_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetScore() const;

protected:

	UPROPERTY(meta = (BindWidget))
		UButton* RestartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenuButton;

	virtual void NativeOnInitialized() override;

private:

	void OnMatchStateChanged(ETPMatchState NewState);
	//void UpdatePlayersStat();

	UFUNCTION()
		void OnRestartGame();

	UFUNCTION()
		void OnBackToMenu();

	UTP_GameInstance* GetTPGameInstance() const;

	ATP_PlayerState* GetTPPlayerState() const;
};
