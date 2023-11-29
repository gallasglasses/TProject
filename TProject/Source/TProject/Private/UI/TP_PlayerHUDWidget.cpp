// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TP_PlayerHUDWidget.h"
#include "GameCore/TP_PlayerState.h"

int32 UTP_PlayerHUDWidget::GetOBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetOBlockCount();
}

int32 UTP_PlayerHUDWidget::GetIBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetIBlockCount();
}

int32 UTP_PlayerHUDWidget::GetSBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetSBlockCount();
}

int32 UTP_PlayerHUDWidget::GetZBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetZBlockCount();
}

int32 UTP_PlayerHUDWidget::GetLBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetLBlockCount();
}

int32 UTP_PlayerHUDWidget::GetJBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetJBlockCount();
}

int32 UTP_PlayerHUDWidget::GetTBlockCount() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetTBlockCount();
}

int32 UTP_PlayerHUDWidget::GetScore() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetScore();
}

int32 UTP_PlayerHUDWidget::GetLevel() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetLevel();
}

int32 UTP_PlayerHUDWidget::GetLines() const
{
	if (!GetTPPlayerState()) return 0;

	return GetTPPlayerState()->GetLines();
}

void UTP_PlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetTPPlayerState()->OnScoreChanged.AddUObject(this, &UTP_PlayerHUDWidget::OnScoreChanged);
}

ATP_PlayerState* UTP_PlayerHUDWidget::GetTPPlayerState() const
{
	if (!GetWorld()) return nullptr;

	const auto PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return nullptr;

	const auto TPPlayerState = Cast<ATP_PlayerState>(PC->PlayerState);
	if (!TPPlayerState) return nullptr;

	return TPPlayerState;
}
