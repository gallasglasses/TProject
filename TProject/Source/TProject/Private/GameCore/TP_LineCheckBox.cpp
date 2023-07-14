// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_LineCheckBox.h"
#include "GameCore/TP_SingleBlock.h"
#include "GameCore/TP_GridManager.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogLineCheckBox, All, All);

// Sets default values
ATP_LineCheckBox::ATP_LineCheckBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>("DefaultScene");
	SetRootComponent(DefaultScene);

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(DefaultScene);
	Box->SetBoxExtent(BoxExtent);
}

// Called when the game starts or when spawned
void ATP_LineCheckBox::BeginPlay()
{
	Super::BeginPlay();
}

void ATP_LineCheckBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto OverlapSingleBlock = Cast<ATP_SingleBlock>(OtherActor);
	if (OverlapSingleBlock)
	{
		SingleBLock = OverlapSingleBlock;
		bIsFulled = true;
		UE_LOG(LogLineCheckBox, Display, TEXT("SingleBlock %s"), *SingleBLock->GetName());
	}

}

// Called every frame
void ATP_LineCheckBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_LineCheckBox::ShiftBlock()
{
	if (BlockShiftAmount != 0)
	{
		UE_LOG(LogLineCheckBox, Display, TEXT("=======OnShiftBlock======="));
		UE_LOG(LogLineCheckBox, Display, TEXT("BoxIndex %i"), BoxIndex);
		UE_LOG(LogLineCheckBox, Display, TEXT("BlockShiftAmount is %i"), BlockShiftAmount);
		UE_LOG(LogLineCheckBox, Display, TEXT("bNeedDeleteBlock is %s"), bNeedDeleteBlock ? TEXT("TRUE") : TEXT("FALSE"));

		UE_LOG(LogLineCheckBox, Display, TEXT("Need to shift block"));
		
		SingleBLock->ShiftBlock(BlockShiftAmount);
		BlockShiftAmount = 0;
		SingleBLock = nullptr;
		bIsFulled = false;
	}
}

void ATP_LineCheckBox::DeleteBlock()
{
	if (bNeedDeleteBlock)
	{
		UE_LOG(LogLineCheckBox, Display, TEXT("=======OnDeleteBlock======="));
		UE_LOG(LogLineCheckBox, Display, TEXT("BoxIndex %i"), BoxIndex);
		UE_LOG(LogLineCheckBox, Display, TEXT("BlockShiftAmount is %i"), BlockShiftAmount);
		UE_LOG(LogLineCheckBox, Display, TEXT("bNeedDeleteBlock is %s"), bNeedDeleteBlock ? TEXT("TRUE") : TEXT("FALSE"));

		UE_LOG(LogLineCheckBox, Display, TEXT("Yes, Need delete line"));
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEmitter, SingleBLock->GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::None, true);
		SingleBLock->Destroy();
		SingleBLock = nullptr;
		bNeedDeleteBlock = false;
		bIsFulled = false;
	}
}

