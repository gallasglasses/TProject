// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TProjectGameModeBase.h"
#include "TP_GridManager.generated.h"

class ATP_LineCheckBox;

DECLARE_MULTICAST_DELEGATE(FOnShiftLinesSignature);
DECLARE_MULTICAST_DELEGATE(FOnDeleteBlockSignature);

UCLASS()
class TPROJECT_API ATP_GridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_GridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
		int32 GridBoxesAmount = 200;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid")
		FVector FirstBoxSpawnPoint = FVector(0.f, -225.f, 50.f);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grid")
		float BoxSpawnStep = 50.f; 
		
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
		TSubclassOf<ATP_LineCheckBox> LineCheckBoxClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnShiftLinesSignature OnShiftLines;
	FOnDeleteBlockSignature OnDeleteBlock;

	void CheckGridRaws(ETPBlockState State);

private:

	void ChangeGrid();

	FTimerHandle ChangeGridTimer;

	TArray<ATP_LineCheckBox*> BoxesGrid;
	TArray<int32> FulledRawsIndexes;

	FVector NextBoxSpawnPoint;

	float TimeToChangeGrid = 1.f;
};
