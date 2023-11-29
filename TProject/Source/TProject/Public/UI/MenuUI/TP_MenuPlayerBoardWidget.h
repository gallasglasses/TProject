// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP_MenuPlayerBoardWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class TPROJECT_API UTP_MenuPlayerBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
		UVerticalBox* PlayerStatBox;

	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerBoardRawWidgetClass;

	virtual void NativeOnInitialized() override;

private:

	void UpdatePlayersStat();

	UFUNCTION()
		void OnStartGame();
};
