// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_FallingBlock.h"
#include "GameCore/TP_SingleBlock.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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
	Cube1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); //ECR_Overlap ECR_Block
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
}

// Called when the game starts or when spawned
void ATP_FallingBlock::BeginPlay()
{
	Super::BeginPlay();

	//const auto RandNumber = FMath::RandRange(0, 6);
	switch (BlockShapeNumber)
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
		Cube2->AddLocalOffset(FVector(0.f, -CubeHeight, 0.f));
		Cube3->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));
		Cube4->AddLocalOffset(FVector(0.f, 2 * CubeHeight, 0.f));

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
		Cube2->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));
		Cube3->AddLocalOffset(FVector(0.f, -CubeHeight, 0.f));
		Cube4->AddLocalOffset(FVector(0.f, -CubeHeight, -CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("4: L-block"));
		break;

		// J-block
	case 5:
		Cube2->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));
		Cube3->AddLocalOffset(FVector(0.f, -CubeHeight, 0.f));
		Cube4->AddLocalOffset(FVector(0.f, CubeHeight, -CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("5: J-block"));
		break;

		// T-block
	case 6:
		Cube2->AddLocalOffset(FVector(0.f, -CubeHeight, 0.f));
		Cube3->AddLocalOffset(FVector(0.f, CubeHeight, 0.f));
		Cube4->AddLocalOffset(FVector(0.f, 0.f, -CubeHeight));

		UE_LOG(LogFallingBlock, Display, TEXT("6: T-block"));
		break;

	default:
		break;
	}

	BlockColor = *BlockColors.Find(*BlockNumbers.Find(BlockShapeNumber));

	Cube1->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
	Cube2->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
	Cube3->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
	Cube4->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));

	//Cube1->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	//Cube2->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	//Cube3->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);
	//Cube4->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

	if (!bIsNextBlock)
	{
		GetWorldTimerManager().SetTimer(DropingBlockTimer, this, &ATP_FallingBlock::DropBlock, TimeToDropBlock, true);
	}
}

// Called every frame
void ATP_FallingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_FallingBlock::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	if (!GetWorld()) return;
	if (BlockShapeNumber == 0) return; // O-shape no need to turn

	AddActorLocalRotation(FRotator(0.f, 0.f, 90.f));

	TArray<USceneComponent*> Childrens;
	DefaultScene->GetChildrenComponents(false, Childrens);
	for (auto Child : Childrens)
	{
		if (!Cast<UStaticMeshComponent>(Child))
		{
			UE_LOG(LogFallingBlock, Display, TEXT("continue"));
			continue;
		}
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypesArray;
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		TArray<AActor*> ActorsToIgnore {GetOwner()};
		TArray<AActor*> OutArray;

		if (UKismetSystemLibrary::BoxOverlapActors(GetWorld(), Child->GetComponentLocation(), BoxOverlapExtent, ObjectTypesArray, AActor::StaticClass(), ActorsToIgnore, OutArray))
		{
			AddActorLocalRotation(FRotator(0.f, 0.f, -90.f));

			UE_LOG(LogFallingBlock, Display, TEXT("unrotate & break"));
			break;
		}
		UE_LOG(LogFallingBlock, Display, TEXT("all clear"));
	}
}

void ATP_FallingBlock::Speed()
{
	//this->CustomTimeDilation = 5.f;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 5.f);
}

void ATP_FallingBlock::StopSpeed()
{
	//this->CustomTimeDilation = 1.f;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void ATP_FallingBlock::MoveLeft()
{
	if (CheckTrace(FVector(0.f, CubeHeight, 0.f), false))
	{
		AddActorWorldOffset(FVector(0.f, -CubeHeight, 0.f));
	}
}

void ATP_FallingBlock::MoveRight()
{
	if (CheckTrace(FVector(0.f, -CubeHeight, 0.f), false))
	{
		AddActorWorldOffset(FVector(0.f, CubeHeight, 0.f));
	}
}

void ATP_FallingBlock::DropBlock()
{
	if (!GetWorld()) return;

	if (!bIsNextBlock)
	{
		if (CheckTrace(FVector(0.f, 0.f, CubeHeight), true))
		{
			AddActorWorldOffset(FVector(0.f, 0.f, -CubeHeight));
		}
		else
		{
			TArray<USceneComponent*> Childrens;
			DefaultScene->GetChildrenComponents(false, Childrens);
			for (auto Child : Childrens)
			{
				//UE_LOG(LogFallingBlock, Display, TEXT("Child"));

				const FTransform SpawnTransform(FRotator::ZeroRotator, Child->GetComponentLocation(), FVector::OneVector);
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				const auto SingleBlock = GetWorld()->SpawnActorDeferred<ATP_SingleBlock>(ATP_SingleBlock::StaticClass(), SpawnTransform); //ATP_SingleBlock::StaticClass()
				if (SingleBlock)
				{
					SingleBlock->SetBlockColor(BlockColor);
					SingleBlock->SetOwner(GetOwner());
					SingleBlock->FinishSpawning(SpawnTransform);

					//UE_LOG(LogFallingBlock, Display, TEXT("SingleBlock FinishSpawning"));
				}
			}

			/*FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParameters;

			auto NewFallingBlock = GetWorld()->SpawnActor<ATP_FallingBlock>(SpawnNewFallingBlockLocation, SpawnRotation, SpawnParameters);*/

			OnTheBottom.Broadcast();

			Destroy();
		}
	}
}

bool ATP_FallingBlock::CheckTrace(const FVector& DirectionToCheck, const bool& IsDropBlock)
{
	if (!GetWorld()) return false;

	bool bShouldDo = true;
	TArray<USceneComponent*> Childrens;
	DefaultScene->GetChildrenComponents(false, Childrens);
	for (auto Child : Childrens)
	{
		FHitResult OutHit;

		const auto Start = Child->GetComponentLocation();
		const auto End = Start - DirectionToCheck;
		FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam; // ignore self?

		if (GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, ECollisionChannel::ECC_WorldStatic, Params))
		{
			bShouldDo = false;
			if (IsDropBlock)
			{
				GetWorldTimerManager().ClearTimer(DropingBlockTimer);
			}
		}
	}

	return bShouldDo;
}

