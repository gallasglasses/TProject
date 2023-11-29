// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TP_PlayerHUDWidget.generated.h"

class UTextBlock;
class ATP_PlayerState;

UCLASS()
class TPROJECT_API UTP_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetOBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetIBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetSBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetZBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetLBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetJBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetTBlockCount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetLevel() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetLines() const; 
		
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void OnScoreChanged();

protected:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* OBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* IBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ZBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* JBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TBlockCountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LinesText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> NiagaraDigitWidgetClass;

	virtual void NativeOnInitialized() override;

private:

	ATP_PlayerState* GetTPPlayerState() const;
};
