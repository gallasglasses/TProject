// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP_PlayerBoardRawWidget.generated.h"

class UTextBlock;
class ATP_PlayerState;

UCLASS()
class TPROJECT_API UTP_PlayerBoardRawWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetScore() const;

protected:

	UPROPERTY( meta = (BindWidget))
		UTextBlock* RankText;

	UPROPERTY( meta = (BindWidget))
		UTextBlock* PlayerText;

	UPROPERTY( meta = (BindWidget))
		UTextBlock* ScoreText;

	UPROPERTY( meta = (BindWidget))
		UTextBlock* PlayCountText;

private:

	ATP_PlayerState* GetTPPlayerState() const;
	
};
