// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_BlockRain.generated.h"

class ATP_FallingBlock;

UCLASS()
class TPROJECT_API ATP_BlockRain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_BlockRain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		FVector SpawnFallingBlockLocation = FVector(0.f, -1500.f, 1500.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid")
		float BlockSpawnStep = 200.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void OnSpawnFallingBlocks();
	void SpawnNewWave();
	void UniformDiscrete();
	void GenerateRandomTimeDrop();
	void SpawnBlock();

	FTimerHandle SpawningBlockTimer;
	FTimerHandle SpawningNewWaveTimer;

	ATP_FallingBlock* CurrentFallingBlock;

	TArray<int32> BlockShapeNumbers;
	TArray<float> BlockDropTimes;

	FVector CurrentBlockSpawnPoint;

	int32 CurrentBlockShapeNumber;
	int32 CurrentIndex;
	int32 BlocksAmount = 15;

	float CurrentTimeToDropBlock;
	float MinTimeToDropBlock = 0.05f;
	float MaxTimeToDropBlock = 1.0f;

};
