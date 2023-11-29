// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP_PauseWidget.generated.h"

class UButton;
class UTP_GameInstance;

UCLASS()
class TPROJECT_API UTP_PauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
		UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
		UButton* BackToMenuButton;

	virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
		void OnContinue();

	UFUNCTION()
		void OnRestart();

	UFUNCTION()
		void OnBackToMenu();

	UTP_GameInstance* GetTPGameInstance() const;
};
