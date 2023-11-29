// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TProjectGameModeBase.generated.h"

UENUM(BlueprintType)
enum class ETPMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

UENUM(BlueprintType)
enum class ETPBlockState : uint8
{
	None = 0,
	BlockFalling,
	BlockFalled
};

class ATP_GridManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ETPMatchState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBlockStateChangedSignature, ETPBlockState);
DECLARE_MULTICAST_DELEGATE(FOnChangedLevelSignature);


UCLASS()
class TPROJECT_API ATProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATProjectGameModeBase();

	virtual void StartPlay() override;

	FOnMatchStateChangedSignature OnMatchStateChanged;
	FOnBlockStateChangedSignature OnBlockStateChanged;
	FOnChangedLevelSignature OnChangedLevel;

	void SetBlockState(ETPBlockState State);
	void SetBlockCount(APlayerController* PC, int32 ShapeNumber);
	void SetScore(APlayerController* PC, int32 Score);
	void SetLines(APlayerController* PC, int32 Lines);
	void GameOver();

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid")
		FVector GridSpawnPoint = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, Category = "Game")
		TSubclassOf<ATP_GridManager> GridClass;

private:

	ETPMatchState MatchState = ETPMatchState::WaitingToStart;
	ETPBlockState BlockState = ETPBlockState::None;

	void SpawnGrid();
	void SetMatchState(ETPMatchState State);
	
};
