#pragma once

#include "CoreMinimal.h"
#include "SaveData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FString PlayerName;

	UPROPERTY()
		int32 MaxScore;

	UPROPERTY()
		int32 PlayCount;

};