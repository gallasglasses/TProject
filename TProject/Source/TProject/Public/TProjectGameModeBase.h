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


UCLASS()
class TPROJECT_API ATProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATProjectGameModeBase();

	virtual void StartPlay() override;

	FOnMatchStateChangedSignature OnMatchStateChanged;
	FOnBlockStateChangedSignature OnBlockStateChanged;

	void SetBlockState(ETPBlockState State);

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
