// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_PlayerController.h"
#include "GameCore/TP_FallingBlock.h"

#include "InputMappingContext.h"
#include "InputAction.h"

void ATP_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    FallingBlock = Cast<ATP_FallingBlock>(GetPawn());
}

// Called to bind functionality to input
void ATP_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    /*check(InputComponent);

    InputComponent->BindAction("Rotate", IE_Pressed, this, &ATP_PlayerController::Rotate);
    InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ATP_PlayerController::MoveLeft);
    InputComponent->BindAction("MoveRight", IE_Pressed, this, &ATP_PlayerController::MoveRight);
    InputComponent->BindAction("Speed", IE_Pressed, this, &ATP_PlayerController::Speed);*/

    PawnMappingContext = NewObject<UInputMappingContext>(this);

    MoveAction = NewObject<UInputAction>(this);
    MoveAction->ValueType = EInputActionValueType::Axis3D;

    PawnMappingContext->MapKey(MoveAction, EKeys::W);
}

void ATP_PlayerController::Rotate()
{
    if (FallingBlock)
    {
        FallingBlock->Rotate();
    }
}

void ATP_PlayerController::Speed()
{
    if (FallingBlock)
    {
        FallingBlock->Speed();
    }
}

void ATP_PlayerController::MoveLeft()
{
    if (FallingBlock)
    {
        FallingBlock->MoveLeft();
    }
}

void ATP_PlayerController::MoveRight()
{
    if (FallingBlock)
    {
        FallingBlock->MoveRight();
    }
}
