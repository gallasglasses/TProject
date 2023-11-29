// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuUI/TP_BlockRain.h"
#include "GameCore/TP_FallingBlock.h"

#include "Kismet/KismetMathLibrary.h"
#include "TP_BlockRain.h"

// Sets default values
ATP_BlockRain::ATP_BlockRain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATP_BlockRain::BeginPlay()
{
	Super::BeginPlay();
	
	OnSpawnFallingBlocks();
}

// Called every frame
void ATP_BlockRain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_BlockRain::OnSpawnFallingBlocks()
{
	if (!GetWorld()) return;

	UniformDiscrete();
	GenerateRandomTimeDrop();
	
	GetWorldTimerManager().SetTimer(SpawningNewWaveTimer, this, &ATP_BlockRain::SpawnNewWave, 10.f, true);
}

void ATP_BlockRain::SpawnNewWave()
{
	CurrentBlockSpawnPoint = SpawnFallingBlockLocation;
	CurrentIndex = 0;
	CurrentBlockShapeNumber = BlockShapeNumbers[CurrentIndex];
	CurrentTimeToDropBlock = BlockDropTimes[CurrentIndex];
	GetWorldTimerManager().SetTimer(SpawningBlockTimer, this, &ATP_BlockRain::SpawnBlock, CurrentTimeToDropBlock, false);

	UE_LOG(LogCameraPawn, Display, TEXT("WAVE DONE"));
	BlockShapeNumbers.Empty();
	UniformDiscrete();
	GenerateRandomTimeDrop();
}

void ATP_BlockRain::UniformDiscrete()
{

	int32 m = FMath::RandRange(2, INT32_MAX);
	int32 a = FMath::RandRange(0, m - 1);
	int32 c = FMath::RandRange(0, m - 1);
	int32 seed = FMath::RandRange(0, m - 1);;

	for (int32 i = 0; i <= BlocksAmount; ++i)
	{
		seed = FMath::Abs((a * seed + c) % m);
		int32 RandNumber = seed % 7;
		BlockShapeNumbers.Add(RandNumber);
		UE_LOG(LogCameraPawn, Display, TEXT("Number [%i] %i"), i, RandNumber);
	}

}

void ATP_BlockRain::GenerateRandomTimeDrop()
{
	if (!BlockDropTimes.Empty())
	{
		for (int32 i = 0; i <= BlocksAmount; ++i)
		{	
			if (BlockDropTimes[i] < (MinTimeToDropBlock + (MaxTimeToDropBlock - MinTimeToDropBlock)/2) )
			{
				BlockDropTimes[i] = UKismetMathLibrary::RandomFloatInRange(MinTimeToDropBlock, BlockDropTimes[i]);
			}
			else
			{
				BlockDropTimes[i] = UKismetMathLibrary::RandomFloatInRange(BlockDropTimes[i], MaxTimeToDropBlock);
			}
			UE_LOG(LogCameraPawn, Display, TEXT("Time [%f] %f"), i, BlockDropTimes[i]);
		}
	}
	else
	{
		for (int32 i = 0; i <= BlocksAmount; ++i)
		{
			BlockDropTimes.Add(UKismetMathLibrary::RandomFloatInRange(MinTimeToDropBlock, MaxTimeToDropBlock));
			UE_LOG(LogCameraPawn, Display, TEXT("Time [%f] %f"), i, BlockDropTimes[i]);
		}
	}
	
}

void ATP_BlockRain::SpawnBlock()
{
	GetWorldTimerManager().ClearTimer(SpawningBlockTimer);
	const FTransform CurrentFallingBlockSpawnTransform(FRotator::ZeroRotator, CurrentBlockSpawnPoint, FVector::OneVector);
	FActorSpawnParameters CurrentFallingBlockSpawnParameters;
	CurrentFallingBlockSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	CurrentFallingBlock = GetWorld()->SpawnActorDeferred<ATP_FallingBlock>(ATP_FallingBlock::StaticClass(), CurrentFallingBlockSpawnTransform);
	if (CurrentFallingBlock)
	{
		CurrentFallingBlock->SetBlockShapeNumber(CurrentBlockShapeNumber);
		CurrentFallingBlock->SetIsNextBlock(false);
		CurrentFallingBlock->SetTimeToDropBlock(CurrentTimeToDropBlock);
		CurrentFallingBlock->SetOwner(GetOwner());
		CurrentFallingBlock->FinishSpawning(CurrentFallingBlockSpawnTransform);

		//UE_LOG(LogCameraPawn, Display, TEXT("CurrentTimeToDropBlock %f"), CurrentTimeToDropBlock);
		UE_LOG(LogCameraPawn, Display, TEXT("CurrentFallingBlock FinishSpawning"));
	}
	CurrentIndex++;
	if (CurrentIndex < BlockShapeNumbers.Num())
	{
		CurrentBlockSpawnPoint.Y += BlockSpawnStep;
		CurrentBlockShapeNumber = BlockShapeNumbers[CurrentIndex];
		CurrentTimeToDropBlock = BlockDropTimes[CurrentIndex];
		GetWorldTimerManager().SetTimer(SpawningBlockTimer, this, &ATP_BlockRain::SpawnBlock, CurrentTimeToDropBlock, false);
	}
}

