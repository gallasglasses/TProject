// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_GridManager.h"
#include "GameCore/TP_LineCheckBox.h"
#include "GameCore/TP_PlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogGridManager, All, All);

// Sets default values
ATP_GridManager::ATP_GridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATP_GridManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnBlockStateChanged.AddUObject(this, &ATP_GridManager::CheckGridRaws);
		}
	}

	NextBoxSpawnPoint = FirstBoxSpawnPoint;
	
	int32 j = 0;
	for (int32 i = 0; i < GridBoxesAmount; i++)
	{	
		if (i == (j + 1) * 10)
		{
			j++;
			NextBoxSpawnPoint = FirstBoxSpawnPoint;
			NextBoxSpawnPoint.Z += j * BoxSpawnStep;
		}
		if (i < (j+1) * 10)
		{
			const FTransform SpawnTransform(FRotator::ZeroRotator, NextBoxSpawnPoint, FVector::OneVector);
			ATP_LineCheckBox* LineCheckBox = GetWorld()->SpawnActorDeferred<ATP_LineCheckBox>(ATP_LineCheckBox::StaticClass(), SpawnTransform);
			if (LineCheckBox)
			{
				LineCheckBox->SetBoxIndex(i);
				LineCheckBox->SetOwner(this);
				LineCheckBox->FinishSpawning(SpawnTransform);
			}

			BoxesGrid.Add(LineCheckBox);
			NextBoxSpawnPoint.Y += BoxSpawnStep;
		}
	}
}

// Called every frame
void ATP_GridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_GridManager::CheckGridRaws(ETPBlockState State)
{
	UE_LOG(LogGridManager, Display, TEXT("CheckGridRaws"));
	
	if (State == ETPBlockState::BlockFalled)
	{
		UE_LOG(LogGridManager, Display, TEXT("BlockFalled"));

		int32 j = 0;
		int32 BoxesCount = 0;

		for (int32 i = 0; i < GridBoxesAmount; )
		{
			if (BoxesGrid[i]->GetIsFulled())
			{
				BoxesCount++;
				i++;
				if (BoxesCount < 10)
				{
					continue;
				}
				else
				{
					FulledRawsIndexes.Add(j);
					BoxesCount = 0;
					j++;
				}
			}
			else
			{

				BoxesCount = 0;
				j++;
				i = j * 10;
			}
		}

		j = 0;
		int32 CountShiftStep = 0;
		
		if (!FulledRawsIndexes.IsEmpty())
		{
			for (int i = 0; i < FulledRawsIndexes.Num(); i++)
			{
				UE_LOG(LogGridManager, Display, TEXT("FulledRawsIndexes [%d] : %d"), i, FulledRawsIndexes[i]);
			}
			for (int32 i = 0; i < GridBoxesAmount; i++)
			{
				if (FulledRawsIndexes.Contains(j))
				{
					BoxesGrid[i]->SetNeedDelete(true);
					UE_LOG(LogGridManager, Display, TEXT("BoxesGrid [%d] : DELETE "), i);

					BoxesGrid[i]->DeleteBlock();
					BoxesCount++;
					if (BoxesCount < 10)
					{
						continue;
					}
					else
					{
						CountShiftStep++;
						BoxesCount = 0;
						j++;
					}
				}
				else
				{
					if (BoxesGrid[i]->GetIsFulled())
					{
						BoxesGrid[i]->SetShiftAmount(CountShiftStep);
					}
					BoxesCount++;
					if (BoxesCount < 10)
					{
						continue;
					}
					else
					{
						BoxesCount = 0;
						j++;
					}
				}
			}

			GetWorldTimerManager().SetTimer(ChangeGridTimer, this, &ATP_GridManager::ChangeGrid, TimeToChangeGrid, false);
		}
		else
		{
			UE_LOG(LogGridManager, Display, TEXT("FulledRawsIndexes IS EMPTY"));
			if (!GetWorld()) return;
			const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
			if (!GameMode) return;

			GameMode->SetBlockState(ETPBlockState::BlockFalling);
		}
	}
}

void ATP_GridManager::ChangeGrid()
{
	GetWorldTimerManager().ClearTimer(ChangeGridTimer);

	for (int32 i = 0; i < GridBoxesAmount; i++)
	{
		if (BoxesGrid[i]->GetIsFulled())
		{
			UE_LOG(LogGridManager, Display, TEXT("BoxesGrid [%d] : SHIFT "), i);
			BoxesGrid[i]->ShiftBlock();
		}
	}

	if (!GetWorld()) return;
	const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto PC = Cast<ATP_PlayerController>(GetWorld()->GetFirstPlayerController());
	if (!PC) return;

	int32 Score = 0;
	switch (FulledRawsIndexes.Num())
	{
	case 0:
		break;

	case 1:
		Score = 40;
		break;

	case 2:
		Score = 100;
		break;

	case 3:
		Score = 300;
		break;

	case 4:
		Score = 1200;
		break;

	default:
		break;
	}

	GameMode->SetScore(PC, Score);
	GameMode->SetLines(PC, FulledRawsIndexes.Num());

	FulledRawsIndexes.Empty();

	GameMode->SetBlockState(ETPBlockState::BlockFalling);
}

