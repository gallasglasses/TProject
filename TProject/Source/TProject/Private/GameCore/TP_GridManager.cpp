// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_GridManager.h"
#include "GameCore/TP_LineCheckBox.h"

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
	
	int j = 0;
	for (int i = 0; i < GridBoxesAmount; i++)
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
			//FActorSpawnParameters SpawnParameters;
			//SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ATP_LineCheckBox* LineCheckBox = GetWorld()->SpawnActorDeferred<ATP_LineCheckBox>(ATP_LineCheckBox::StaticClass(), SpawnTransform);
			if (LineCheckBox)
			{
				LineCheckBox->SetBoxIndex(i);
				LineCheckBox->SetOwner(this);
				LineCheckBox->FinishSpawning(SpawnTransform);

				//UE_LOG(LogGridManager, Display, TEXT("GetOwner()->GetName() %s"), *this->GetName());
			}

			BoxesGrid.Add(LineCheckBox);
			//LineCheckBox->OnBoxFulled.AddUObject(this, &ATP_GridManager::OnBoxFulled);
			//LineCheckBox->OnDeleteBlock.AddUObject(this, &ATP_GridManager::OnDeleteBlock);
			NextBoxSpawnPoint.Y += BoxSpawnStep;
		}
		
	}

	UE_LOG(LogGridManager, Display, TEXT("LineCheckBoxes.Num() %i"), BoxesGrid.Num());
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

		int j = 0;
		int BoxesCount = 0;

		for (int i = 0; i < GridBoxesAmount; )
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
		int CountShiftStep = 0;

		if (!FulledRawsIndexes.IsEmpty())
		{
			for (int i = 0; i < GridBoxesAmount; i++)
			{
				if (FulledRawsIndexes.Contains(j))
				{
					BoxesGrid[i]->SetNeedDelete(true);
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
		}

		ChangeGrid();

		if (GetWorld())
		{
			const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
			if (GameMode)
			{
				GameMode->SetBlockState(ETPBlockState::BlockFalling);
			}
		}
	}
}

void ATP_GridManager::ChangeGrid()
{
	for (int i = 0; i < GridBoxesAmount; i++)
	{
		if (BoxesGrid[i]->GetIsFulled())
		{
			BoxesGrid[i]->ShiftBlock();
		}
	}

	FulledRawsIndexes.Empty();
}

