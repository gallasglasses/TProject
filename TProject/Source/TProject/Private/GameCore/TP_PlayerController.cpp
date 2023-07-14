// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_PlayerController.h"
#include "GameCore/TP_FallingBlock.h"

#include "InputMappingContext.h"
#include "InputAction.h"

void ATP_PlayerController::BeginPlay()
{
    Super::BeginPlay();
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

    /*MoveAction = NewObject<UInputAction>(this);
    MoveAction->ValueType = EInputActionValueType::Axis3D;
    PawnMappingContext->MapKey(MoveAction, EKeys::S);*/

    RotateAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(RotateAction, EKeys::W);

    MoveRightAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(MoveRightAction, EKeys::D);

    MoveLeftAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(MoveLeftAction, EKeys::A);

    SpeedAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(SpeedAction, EKeys::S);
}
