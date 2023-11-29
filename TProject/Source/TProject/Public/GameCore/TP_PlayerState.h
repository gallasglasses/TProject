// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TP_PlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnScoreChangedSignature);

UCLASS()
class TPROJECT_API ATP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	void AddOBlock() { ++OBlockCount; }
	int32 GetOBlockCount() const { return OBlockCount; }

	void AddIBlock() { ++IBlockCount; }
	int32 GetIBlockCount() const { return IBlockCount; }

	void AddSBlock() { ++SBlockCount; }
	int32 GetSBlockCount() const { return SBlockCount; }

	void AddZBlock() { ++ZBlockCount; }
	int32 GetZBlockCount() const { return ZBlockCount; }

	void AddLBlock() { ++LBlockCount; }
	int32 GetLBlockCount() const { return LBlockCount; }

	void AddJBlock() { ++JBlockCount; }
	int32 GetJBlockCount() const { return JBlockCount; }

	void AddTBlock() { ++TBlockCount; }
	int32 GetTBlockCount() const { return TBlockCount; }

	void AddPlayCount() { ++PlayCount; }
	int32 GetPlayCount() const { return PlayCount; }

	void SetScore(int32 Points);
	int32 GetScore() const { return Score; }

	void SetMaxScore(int32 Points) { MaxScore = Points; };
	int32 GetMaxScore() const { return MaxScore; }

	void SetLevel() { Level = Lines / 10; }
	int32 GetLevel() const { return Level; }

	void SetLines(int32 Amount) { Lines = Amount; }
	int32 GetLines() const { return Lines; }
	
	void LogInfo();

	FOnScoreChangedSignature OnScoreChanged;

private:

	int32 OBlockCount = 0;
	int32 IBlockCount = 0;
	int32 SBlockCount = 0;
	int32 ZBlockCount = 0;
	int32 LBlockCount = 0;
	int32 JBlockCount = 0;
	int32 TBlockCount = 0;

	int32 MaxScore = 0;
	int32 Score = 0;
	int32 Level = 0;
	int32 Lines = 0;
	int32 PlayCount = 0;

	FString Player;
	
};
