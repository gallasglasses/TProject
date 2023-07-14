// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TProjectGameModeBase.h"
#include "TP_CameraPawn.generated.h"

class UCameraComponent;
class ATP_FallingBlock;
class UFloatingPawnMovement;

UCLASS()
class TPROJECT_API ATP_CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATP_CameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		FVector SpawnCurrentFallingBlockLocation = FVector(0.f, 25.f, 1000.f);

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		FVector SpawnNextFallingBlockLocation = FVector(0.f, 425.f, 1000.f);

#pragma region /** Input */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputMappingContext* InputMapping;

#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void Move(const struct FInputActionValue& ActionValue);

	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
		float MoveScale;

private:
	
	ATP_FallingBlock* CurrentFallingBlock;
	ATP_FallingBlock* NextFallingBlock;

	UFUNCTION()
		void OnSpawnNewFallingBlock(ETPBlockState State);

	void Rotate();
	void MoveRight();
	void MoveLeft();
	void Speed();
	void StopRotate();
	void StopMoveRight();
	void StopMoveLeft();
	void StopSpeed();
	void UniformDiscrete();
	void OnTheBottom();

	TArray<int> BlockShapeNumbers;

	bool bIsRotateOnce = false;
	bool bIsMoveRightOnce = false;
	bool bIsMoveLeftOnce = false;
	bool bIsSpeedOnce = false;
	bool bIsFirstMove = true;

	int CurrentBlockShapeNumber;
	int NextBlockShapeNumber;
	int CurrentMove = 0;
};
