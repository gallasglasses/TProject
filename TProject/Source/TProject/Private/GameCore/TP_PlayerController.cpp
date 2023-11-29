// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_PlayerController.h"
#include "GameCore/TP_FallingBlock.h"
#include "GameCore/TP_CameraPawn.h"
#include "TProjectGameModeBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

DEFINE_LOG_CATEGORY_STATIC(LogATP_PlayerController, All, All);

void ATP_PlayerController::BeginPlay()
{
    Super::BeginPlay();
    TP_Pawn = Cast<ATP_CameraPawn>(GetPawn());

    if (GetWorld())
    {
        const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ATP_PlayerController::OnMatchStateChanged);
        }
    }
}

// Called to bind functionality to input
void ATP_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    PawnMappingContext = NewObject<UInputMappingContext>(this);

    /*MoveAction = NewObject<UInputAction>(this);
    MoveAction->ValueType = EInputActionValueType::Axis3D;
    PawnMappingContext->MapKey(MoveAction, EKeys::S);*/

    RotateAction = NewObject<UInputAction>(this);
    RotateAction->ValueType = EInputActionValueType::Boolean;
    PawnMappingContext->MapKey(RotateAction, EKeys::W);

    MoveRightAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(MoveRightAction, EKeys::D);

    MoveLeftAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(MoveLeftAction, EKeys::A);

    SpeedAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(SpeedAction, EKeys::S);

    PauseAction = NewObject<UInputAction>(this);
    PawnMappingContext->MapKey(PauseAction, EKeys::SpaceBar);

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);

    EIC->BindAction(this->PauseAction, ETriggerEvent::Triggered, this, &ATP_PlayerController::OnPauseGame);

    EIC->BindAction(this->RotateAction, ETriggerEvent::Triggered, this, &ATP_PlayerController::Rotate);
    EIC->BindAction(this->RotateAction, ETriggerEvent::Completed, this, &ATP_PlayerController::StopRotate);

    EIC->BindAction(this->MoveRightAction, ETriggerEvent::Triggered, this, &ATP_PlayerController::MoveRight);
    EIC->BindAction(this->MoveRightAction, ETriggerEvent::Completed, this, &ATP_PlayerController::StopMoveRight);

    EIC->BindAction(this->MoveLeftAction, ETriggerEvent::Triggered, this, &ATP_PlayerController::MoveLeft);
    EIC->BindAction(this->MoveLeftAction, ETriggerEvent::Completed, this, &ATP_PlayerController::StopMoveLeft);

    EIC->BindAction(this->SpeedAction, ETriggerEvent::Triggered, this, &ATP_PlayerController::Speed);
    EIC->BindAction(this->SpeedAction, ETriggerEvent::Completed, this, &ATP_PlayerController::StopSpeed);

    ULocalPlayer* LocalPlayer = this->GetLocalPlayer();
    UE_LOG(LogATP_PlayerController, Display, TEXT("GetPawn() : %s"), *this->GetLocalPlayer()->GetName());
    check(LocalPlayer);
    
    UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    check(Subsystem);

    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(this->PawnMappingContext, 0);
}

void ATP_PlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ATP_PlayerController::OnMatchStateChanged(ETPMatchState State)
{
    if (State == ETPMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ATP_PlayerController::Rotate()
{
    if (TP_Pawn)
    {
        TP_Pawn->Rotate();
    }
}

void ATP_PlayerController::MoveRight()
{
    if (TP_Pawn)
    {
        TP_Pawn->MoveRight();
    }
}

void ATP_PlayerController::MoveLeft()
{
    if (TP_Pawn)
    {
        TP_Pawn->MoveLeft();
    }
}

void ATP_PlayerController::Speed()
{
    if (TP_Pawn)
    {
        TP_Pawn->Speed();
    }
}

void ATP_PlayerController::StopRotate()
{
    if (TP_Pawn)
    {
        TP_Pawn->StopRotate();
    }
}

void ATP_PlayerController::StopMoveRight()
{
    if (TP_Pawn)
    {
        TP_Pawn->StopMoveRight();
    }
}

void ATP_PlayerController::StopMoveLeft()
{
    if (TP_Pawn)
    {
        TP_Pawn->StopMoveLeft();
    }
}

void ATP_PlayerController::StopSpeed()
{
    if (TP_Pawn)
    {
        TP_Pawn->StopSpeed();
    }
}
