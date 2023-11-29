// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_CameraPawn.h"
#include "GameCore/TP_FallingBlock.h"
#include "GameCore/TP_PlayerController.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

DEFINE_LOG_CATEGORY_STATIC(LogCameraPawn, All, All);

// Sets default values
ATP_CameraPawn::ATP_CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SetRootComponent(Camera);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	MoveScale = 1.f;
}

// Called when the game starts or when spawned
void ATP_CameraPawn::BeginPlay()
{
	Super::BeginPlay();

	/*FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;

	FallingBlock = GetWorld()->SpawnActor<ATP_FallingBlock>(SpawnNewFallingBlockLocation, SpawnRotation, SpawnParameters);*/

	if (GetWorld())
	{
		const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnBlockStateChanged.AddUObject(this, &ATP_CameraPawn::OnSpawnNewFallingBlock);
			GameMode->OnChangedLevel.AddUObject(this, &ATP_CameraPawn::OnChangedLevel);
		}
	}

	CurrentTimeToDropBlock = TimeToDropBlock;
}

// Called every frame
void ATP_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void ATP_CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
//	ATP_PlayerController* PC = Cast<ATP_PlayerController>(GetController());
//	check(EIC && PC);
//
//	//EIC->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &ATP_CameraPawn::Move);
//
//	EIC->BindAction(PC->RotateAction, ETriggerEvent::Triggered, this, &ATP_CameraPawn::Rotate);
//	EIC->BindAction(PC->RotateAction, ETriggerEvent::Completed, this, &ATP_CameraPawn::StopRotate);
//
//	EIC->BindAction(PC->MoveRightAction, ETriggerEvent::Triggered, this, &ATP_CameraPawn::MoveRight);
//	EIC->BindAction(PC->MoveRightAction, ETriggerEvent::Completed, this, &ATP_CameraPawn::StopMoveRight);
//
//	EIC->BindAction(PC->MoveLeftAction, ETriggerEvent::Triggered, this, &ATP_CameraPawn::MoveLeft);
//	EIC->BindAction(PC->MoveLeftAction, ETriggerEvent::Completed, this, &ATP_CameraPawn::StopMoveLeft);
//
//	EIC->BindAction(PC->SpeedAction, ETriggerEvent::Triggered, this, &ATP_CameraPawn::Speed);
//	EIC->BindAction(PC->SpeedAction, ETriggerEvent::Completed, this, &ATP_CameraPawn::StopSpeed);
//	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
//	check(LocalPlayer);
//
//	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
//	check(Subsystem);
//
//	Subsystem->ClearAllMappings();
//	Subsystem->AddMappingContext(PC->PawnMappingContext, 0);
//}

//void ATP_CameraPawn::Move(const FInputActionValue& ActionValue)
//{
//	//UE_LOG(LogCameraPawn, Display, TEXT("MOVE"));
//	FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
//	AddMovementInput(GetActorRotation().RotateVector(Input), MoveScale);
//}

void ATP_CameraPawn::OnSpawnNewFallingBlock(ETPBlockState State)
{
	if (State == ETPBlockState::BlockFalling)
	{
		UE_LOG(LogCameraPawn, Display, TEXT("BlockFalled"));
	
		if (bIsFirstMove)
		{
			/*CurrentBlockShapeNumber = FMath::RandRange(0, 6);
			NextBlockShapeNumber = FMath::RandRange(0, 6);*/
			UniformDiscrete();
			CurrentBlockShapeNumber = BlockShapeNumbers[0];
			NextBlockShapeNumber = BlockShapeNumbers[1];
			bIsFirstMove = false;
			UE_LOG(LogCameraPawn, Display, TEXT("bIsFirstMove = false"));
		}
		else
		{
			if (NextFallingBlock)
			{
				NextFallingBlock->Destroy();
			}
			CurrentBlockShapeNumber = NextBlockShapeNumber;
			CurrentMove < 6 ? ++CurrentMove : CurrentMove = 0;
			UE_LOG(LogCameraPawn, Display, TEXT("Current Move : %i"), CurrentMove);

			if (CurrentMove + 1 <= 6)
			{
				NextBlockShapeNumber = BlockShapeNumbers[CurrentMove + 1];

				UE_LOG(LogCameraPawn, Display, TEXT("Next Move : %i"), CurrentMove + 1);
			}
			else
			{
				BlockShapeNumbers.Empty();
				UniformDiscrete();
				NextBlockShapeNumber = BlockShapeNumbers[0];

				UE_LOG(LogCameraPawn, Display, TEXT("Next Move : 0"));
			}
		}

		if (!GetWorld()) return;
		const FTransform CurrentFallingBlockSpawnTransform(FRotator::ZeroRotator, SpawnCurrentFallingBlockLocation, FVector::OneVector);
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

			UE_LOG(LogCameraPawn, Display, TEXT("CurrentTimeToDropBlock %f"), CurrentTimeToDropBlock);
			UE_LOG(LogCameraPawn, Display, TEXT("CurrentFallingBlock FinishSpawning"));
		}

		const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		const auto PC = Cast<ATP_PlayerController>(GetController());
		if (!PC) return;

		GameMode->SetBlockCount(PC, CurrentBlockShapeNumber);

		CurrentFallingBlock->OnTheBottom.AddUObject(this, &ATP_CameraPawn::OnTheBottom);

		const FTransform NextFallingBlockSpawnTransform(FRotator::ZeroRotator, SpawnNextFallingBlockLocation, FVector::OneVector);
		FActorSpawnParameters NextFallingBlockSpawnParameters;
		NextFallingBlockSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		NextFallingBlock = GetWorld()->SpawnActorDeferred<ATP_FallingBlock>(ATP_FallingBlock::StaticClass(), NextFallingBlockSpawnTransform);
		if (NextFallingBlock)
		{
			NextFallingBlock->SetBlockShapeNumber(NextBlockShapeNumber);
			NextFallingBlock->SetIsNextBlock(true);
			NextFallingBlock->SetOwner(GetOwner());
			NextFallingBlock->FinishSpawning(NextFallingBlockSpawnTransform);

			UE_LOG(LogCameraPawn, Display, TEXT("NextFallingBlock FinishSpawning"));
		}
	}
}

void ATP_CameraPawn::OnChangedLevel()
{
	UE_LOG(LogCameraPawn, Display, TEXT("TimeToDropBlock %f"), CurrentTimeToDropBlock);

	CurrentTimeToDropBlock -= DeltaTimeToDropBlock;

	UE_LOG(LogCameraPawn, Display, TEXT("New TimeToDropBlock %f"), CurrentTimeToDropBlock);
}

void ATP_CameraPawn::Rotate()
{
	if (!bIsRotateOnce)
	{
		CurrentFallingBlock->Rotate();
		bIsRotateOnce = !bIsRotateOnce;
	}
}

void ATP_CameraPawn::MoveRight()
{
	if (!bIsMoveRightOnce)
	{
		CurrentFallingBlock->MoveRight();
		bIsMoveRightOnce = !bIsMoveRightOnce;
	}
}

void ATP_CameraPawn::MoveLeft()
{
	if (!bIsMoveLeftOnce)
	{
		CurrentFallingBlock->MoveLeft();
		bIsMoveLeftOnce = !bIsMoveLeftOnce;
	}
}

void ATP_CameraPawn::Speed()
{
	if (!bIsSpeedOnce)
	{
		CurrentFallingBlock->Speed();
		bIsSpeedOnce = !bIsSpeedOnce;
	}
}

void ATP_CameraPawn::StopRotate()
{
	if (bIsRotateOnce)
	{
		bIsRotateOnce = !bIsRotateOnce;
	}
}

void ATP_CameraPawn::StopMoveRight()
{
	if (bIsMoveRightOnce)
	{
		bIsMoveRightOnce = !bIsMoveRightOnce;
	}
}

void ATP_CameraPawn::StopMoveLeft()
{
	if (bIsMoveLeftOnce)
	{
		bIsMoveLeftOnce = !bIsMoveLeftOnce;
	}
}

void ATP_CameraPawn::StopSpeed()
{
	if (bIsSpeedOnce)
	{
		CurrentFallingBlock->StopSpeed();
		bIsSpeedOnce = !bIsSpeedOnce;
	}
}

void ATP_CameraPawn::UniformDiscrete()
{
	/*float Number = FMath::Rand() * 7 / RAND_MAX;
	int RandNumber = FMath::RoundToInt(Number);*/

	//int RandNumber = FMath::Rand() % 7;
	
	int32 m = FMath::RandRange(2, INT32_MAX);
	//UE_LOG(LogCameraPawn, Display, TEXT("Number m %i"), m);

	int32 a = FMath::RandRange(0, m - 1);
	//UE_LOG(LogCameraPawn, Display, TEXT("Number a %i"), a);

	int32 c = FMath::RandRange(0, m - 1);
	//UE_LOG(LogCameraPawn, Display, TEXT("Number c %i"), c);

	int32 seed = FMath::RandRange(0, m - 1);;
	//UE_LOG(LogCameraPawn, Display, TEXT("Number seed %i"), seed);

	for (int32 i = 0; i < 7; ++i)
	{
		seed = FMath::Abs((a * seed + c) % m);
		int32 RandNumber = seed % 7;
		BlockShapeNumbers.Add(RandNumber);
		UE_LOG(LogCameraPawn, Display, TEXT("Number [%i] %i"), i, RandNumber);
	}
	
}

void ATP_CameraPawn::OnTheBottom(FVector CurrentLocation)
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<ATProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	if (CurrentLocation == SpawnCurrentFallingBlockLocation)
	{
		GameMode->GameOver();
	}
	else
	{
		GameMode->SetBlockState(ETPBlockState::BlockFalled);
	}
}

