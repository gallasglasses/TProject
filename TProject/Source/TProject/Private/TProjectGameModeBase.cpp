// Copyright Epic Games, Inc. All Rights Reserved.


#include "TProjectGameModeBase.h"
#include "GameCore/TP_CameraPawn.h"
#include "GameCore/TP_GridManager.h"
#include "GameCore/TP_PlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

ATProjectGameModeBase::ATProjectGameModeBase()
{
	//DefaultPawnClass = ATP_CameraPawn::StaticClass();
	PlayerControllerClass = ATP_PlayerController::StaticClass();
}

void ATProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnGrid();
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
