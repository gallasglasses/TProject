// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP_MainMenuWidget.generated.h"

class UButton;
class UTP_GameInstance;

UCLASS()
class TPROJECT_API UTP_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

	virtual void NativeOnInitialized() override;
	
private:

	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnQuitGame();

	UTP_GameInstance* GetTPGameInstance() const;
};
