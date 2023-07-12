// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_FallingBlock.h"
#include "GameCore/TP_PlayerController.h"
#include "GameCore/TP_SingleBlock.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

DEFINE_LOG_CATEGORY_STATIC(LogFallingBlock, All, All);

// Sets default values
ATP_FallingBlock::ATP_FallingBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>("DefaultScene");
	SetRootComponent(DefaultScene);

	Cube1 = CreateDefaultSubobject<UStaticMeshComponent>("Cube1");
	Cube1->SetupAttachment(DefaultScene);
	Cube1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Cube1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//Cube1->SetCollisionProfileName("OverlapAll");
	//Cube1->SetCollisionProfileName("BlockAll");

	Cube2 = CreateDefaultSubobject<UStaticMeshComponent>("Cube2");
	Cube2->SetupAttachment(DefaultScene);
	Cube2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Cube2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//Cube2->SetCollisionProfileName("OverlapAll");
	//Cube2->SetCollisionProfileName("BlockAll");

	Cube3 = CreateDefaultSubobject<UStaticMeshComponent>("Cube3");
	Cube3->SetupAttachment(DefaultScene);
	Cube3->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Cube3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//Cube3->SetCollisionProfileName("OverlapAll");
	//Cube3->SetCollisionProfileName("BlockAll");

	Cube4 = CreateDefaultSubobject<UStaticMeshComponent>("Cube4");
	Cube4->SetupAttachment(DefaultScene);
	Cube4->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Cube4->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//Cube4->SetCollisionProfileName("OverlapAll");
	//Cube4->SetCollisionProfileName("BlockAll");

	UStaticMesh* CubeMeshTemp = LoadObject<UStaticMesh>(this, *CubeMeshPath);
	if (CubeMeshTemp)
	{
		Cube1->SetStaticMesh(CubeMeshTemp);
		Cube2->SetStaticMesh(CubeMeshTemp);
		Cube3->SetStaticMesh(CubeMeshTemp);
		Cube4->SetStaticMesh(CubeMeshTemp);
	}
	
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	MoveScale = 1.f;
}

// Called when the game starts or when spawned
void ATP_FallingBlock::BeginPlay()
{
	Super::BeginPlay();

	const auto RandNumber = FMath::RandRange(0, 6);
	switch (RandNumber)
	{
		// O-block
	case 0:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));
		Cube4->AddLocalOffset(FVector(0.f, CubeHeight, CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("0: O-block"));
		break;

		// I-block
	case 1:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, 0.f, 2* CubeHeight));
		Cube4->AddLocalOffset(FVector(0.f, 0.f, 3* CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("1: I-block"));
		break;

		// S-block
	case 2:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, -CubeHeight, 0.f));
		Cube4->AddLocalOffset(FVector(0.f, CubeHeight, CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("2: S-block"));
		break;

		// Z-block
	case 3:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, -CubeHeight, CubeHeight));
		Cube4->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));

		UE_LOG(LogFallingBlock, Display, TEXT("3: Z-block"));
		break;

		// L-block
	case 4:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, 0.f, 2* CubeHeight));
		Cube4->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));

		UE_LOG(LogFallingBlock, Display, TEXT("4: L-block"));
		break;

		// J-block
	case 5:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, 0.f, 2* CubeHeight));
		Cube4->AddLocalOffset(FVector(0.f, -CubeHeight, 0.f));

		UE_LOG(LogFallingBlock, Display, TEXT("5: J-block"));
		break;

		// T-block
	case 6:
		Cube2->AddLocalOffset(FVector(0.f, 0.f, CubeHeight));
		Cube3->AddLocalOffset(FVector(0.f, CubeHeight, CubeHeight));
		Cube4->AddLocalOffset(FVector(0.f, -CubeHeight, CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("6: T-block"));
		break;

	default:
		break;
	}

	BlockColor = *BlockColors.Find(*BlockNumbers.Find(RandNumber));

	Cube1->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
	Cube2->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
	Cube3->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
	Cube4->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));

	Cube1->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	Cube2->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	Cube3->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	Cube4->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

	GetWorldTimerManager().SetTimer(DropingBlockTimer, this, &ATP_FallingBlock::DropBlock, TimeToDropBlock, true);

}

// Called every frame
void ATP_FallingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_FallingBlock::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ATP_PlayerController* PC = Cast<ATP_PlayerController>(Controller);
	check(EIC && PC);

	EIC->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &ATP_FallingBlock::Move);
	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMapings();
	Subsystem->AddMappingContext(PC->PawnMappingContext, 0);
}

void ATP_FallingBlock::Move(const FInputActionValue& ActionValue)
{
	FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
	AddMovementInput(GetActorRotation().RotateVector(Input), MoveScale);
}

void ATP_FallingBlock::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogFallingBlock, Display, TEXT("OnComponentBeginOverlap"));
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{

		UE_LOG(LogFallingBlock, Display, TEXT("ECC_WorldStatic"));
	}
}

void ATP_FallingBlock::Rotate()
{
	AddActorLocalRotation(FRotator(90.f, 0.f, 0.f));
}

void ATP_FallingBlock::Speed()
{
	
}

void ATP_FallingBlock::MoveLeft()
{
	
}

void ATP_FallingBlock::MoveRight()
{
}

void ATP_FallingBlock::DropBlock()
{
	bShouldDrop = true;
	TArray<USceneComponent*> Childrens;
	DefaultScene->GetChildrenComponents(false, Childrens);
	for (auto Child : Childrens)
	{
		FHitResult OutHit;

		const auto Start = Child->GetComponentLocation();
		const auto End = Start - FVector(0.f, 0.f, CubeHeight);
		FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam; // ignore self?
		
		if (GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, ECollisionChannel::ECC_WorldStatic, Params))
		{
			bShouldDrop = false;
			GetWorldTimerManager().ClearTimer(DropingBlockTimer);
		}
	}

	if (bShouldDrop)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, -CubeHeight));
	}
	else
	{
		DefaultScene->GetChildrenComponents(false, Childrens);
		for (auto Child : Childrens)
		{
			UE_LOG(LogFallingBlock, Display, TEXT("Child"));
			const auto SpawnSingleBlockLocation = Child->GetComponentLocation();

			const FTransform SpawnTransform(FRotator::ZeroRotator, Child->GetComponentLocation(), FVector::OneVector);
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			const auto SingleBlock = GetWorld()->SpawnActorDeferred<ATP_SingleBlock>(ATP_SingleBlock::StaticClass(), SpawnTransform); //ATP_SingleBlock::StaticClass()
			if (SingleBlock)
			{
				SingleBlock->SetBlockColor(BlockColor);
				SingleBlock->SetOwner(GetOwner());
				SingleBlock->FinishSpawning(SpawnTransform);

				UE_LOG(LogFallingBlock, Display, TEXT("SingleBlock FinishSpawning"));
			}
		}
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParameters;

		auto NewFallingBlock = GetWorld()->SpawnActor<ATP_FallingBlock>(SpawnNewFallingBlockLocation, SpawnRotation, SpawnParameters);
		Destroy();
	}
}

