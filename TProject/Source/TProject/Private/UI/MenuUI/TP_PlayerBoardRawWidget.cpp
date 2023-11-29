// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_PlayerBoardRawWidget.h"
#include "GameCore/TP_PlayerState.h"

int32 UTP_PlayerBoardRawWidget::GetScore() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetScore();
}

ATP_PlayerState* UTP_PlayerBoardRawWidget::GetTPPlayerState() const
{
	if (!GetWorld()) return nullptr;

	const auto PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return nullptr;

	const auto TPPlayerState = Cast<ATP_PlayerState>(PC->PlayerState);
	if (!TPPlayerState) return nullptr;

	return TPPlayerState;
}