// Copyright Epic Games, Inc. All Rights Reserved.


#include "TProjectGameModeBase.h"
#include "GameCore/TP_CameraPawn.h"
#include "GameCore/TP_GridManager.h"
#include "GameCore/TP_PlayerController.h"
#include "GameCore/TP_PlayerState.h"
#include "UI/TP_GameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

ATProjectGameModeBase::ATProjectGameModeBase()
{
	DefaultPawnClass = ATP_CameraPawn::StaticClass();
	PlayerControllerClass = ATP_PlayerController::StaticClass();
	PlayerStateClass = ATP_PlayerState::StaticClass();
	HUDClass = ATP_GameHUD::StaticClass();
}

void ATProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnGrid();

	SetMatchState(ETPMatchState::InProgress);
	SetBlockState(ETPBlockState::BlockFalling);
}

void ATProjectGameModeBase::SpawnGrid()
{
	if (!GetWorld()) return;

	const FTransform SpawnTransform(FRotator::ZeroRotator, GridSpawnPoint, FVector::OneVector);
	FActorSpawnParameters GridSpawnInfo;
	GridSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const auto Grid = GetWorld()->SpawnActor<ATP_GridManager>(GridClass, GridSpawnInfo);
}

void ATProjectGameModeBase::SetMatchState(ETPMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

void ATProjectGameModeBase::SetBlockState(ETPBlockState State)
{
	if (BlockState == State) return;

	BlockState = State;
	if (BlockState == ETPBlockState::BlockFalling)
	{
		UE_LOG(LogGameModeBase, Display, TEXT("BlockFalling"));
	}
	if (BlockState == ETPBlockState::BlockFalled)
	{
		UE_LOG(LogGameModeBase, Display, TEXT("BlockFalled"));
	}

	OnBlockStateChanged.Broadcast(BlockState);
}

void ATProjectGameModeBase::SetBlockCount(APlayerController* PC, int32 ShapeNumber)
{
	const auto PlayerState = PC ? Cast<ATP_PlayerState>(PC->PlayerState) : nullptr;
	if(!PlayerState) return;

	switch (ShapeNumber)
	{
		// O-block
	case 0:
		PlayerState->AddOBlock();
		break;

		// I-block
	case 1:
		PlayerState->AddIBlock();
		break;

		// S-block
	case 2:
		PlayerState->AddSBlock();
		break;

		// Z-block
	case 3:
		PlayerState->AddZBlock();
		break;

		// L-block
	case 4:
		PlayerState->AddLBlock();
		break;

		// J-block
	case 5:
		PlayerState->AddJBlock();
		break;

		// T-block
	case 6:
		PlayerState->AddTBlock();
		break;

	default:
		break;
	}

	PlayerState->LogInfo();
}

void ATProjectGameModeBase::SetScore(APlayerController* PC, int32 Score)
{
	const auto PlayerState = PC ? Cast<ATP_PlayerState>(PC->PlayerState) : nullptr;
	if (!PlayerState) return;

	PlayerState->SetScore(PlayerState->GetScore() + Score * (PlayerState->GetLevel() + 1));
}

void ATProjectGameModeBase::SetLines(APlayerController* PC, int32 Lines)
{
	const auto PlayerState = PC ? Cast<ATP_PlayerState>(PC->PlayerState) : nullptr;
	if (!PlayerState) return;

	PlayerState->SetLines(PlayerState->GetLines() + Lines);
	int32 CheckLinesLevel = PlayerState->GetLines() / 10;
	if (CheckLinesLevel > PlayerState->GetLevel())
	{
		PlayerState->SetLevel();
		OnChangedLevel.Broadcast();
	}
}

void ATProjectGameModeBase::GameOver()
{
	UE_LOG(LogGameModeBase, Display, TEXT("============== GAME OVER =============="));

	SetMatchState(ETPMatchState::GameOver);
}

bool ATProjectGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		SetMatchState(ETPMatchState::Pause);
	}

	return PauseSet;
}

bool ATProjectGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(ETPMatchState::InProgress);
	}
	return PauseCleared;
}
