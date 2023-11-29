// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPPlayerState, All, All);

void ATP_PlayerState::SetScore(int32 Points)
{
	Score = Points;
	OnScoreChanged.Broadcast();
}

void ATP_PlayerState::LogInfo()
{
	UE_LOG(LogTPPlayerState, Display, 
		TEXT("OBlockCount: %i, IBlockCount: %i, SBlockCount: %i, ZBlockCount: %i, LBlockCount: %i, JBlockCount: %i, TBlockCount: %i"), 
		OBlockCount, IBlockCount, SBlockCount, ZBlockCount, LBlockCount, JBlockCount, TBlockCount);
}
