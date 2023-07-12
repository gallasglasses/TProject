// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TP_PlayerController.generated.h"

class ATP_FallingBlock;

class UInputMappingContext;
class UInputAction;

UCLASS()
class TPROJECT_API ATP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY()
	UInputMappingContext* PawnMappingContext;

	UPROPERTY()
	UInputAction* MoveAction;

private:

	UPROPERTY()
		ATP_FallingBlock* FallingBlock;

	void Rotate();
	void Speed();
	void MoveLeft();
	void MoveRight();
	
};
