// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_LineCheckBox.h"
#include "GameCore/TP_SingleBlock.h"
#include "GameCore/TP_GridManager.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"

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

	DestroyNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("DestroyNiagaraComponent");
	DestroyNiagaraComponent->SetupAttachment(Box);

	DestroyNiagaraEffect = LoadObject<UNiagaraSystem>(this, *DestroyNiagaraEffectPath);
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
	if (OverlapSingleBlock && SingleBLock != OverlapSingleBlock)
	{
		if (OverlapSingleBlock->IsShiftingBlock())
		{
			if (IsBlockOnSpot(OverlapSingleBlock))
			{
				SingleBLock = OverlapSingleBlock;
				SingleBLock->SetBLockIndex(BoxIndex);
				bIsFulled = true;
				UE_LOG(LogLineCheckBox, Display, TEXT("Shifting Block On Spot: "));
				UE_LOG(LogLineCheckBox, Display, TEXT("BoxIndex %i | BLockIndex %i | SingleBlock %s"), BoxIndex, SingleBLock->GetBlockIndex(), *SingleBLock->GetName());
			}
		}
		else
		{
			SingleBLock = OverlapSingleBlock;
			SingleBLock->SetBLockIndex(BoxIndex);
			bIsFulled = true;
			UE_LOG(LogLineCheckBox, Display, TEXT("New Block On Spot: "));
			UE_LOG(LogLineCheckBox, Display, TEXT("BoxIndex %i | BLockIndex %i | SingleBlock %s"), BoxIndex, SingleBLock->GetBlockIndex(), *SingleBLock->GetName());
		}
	}

}

// Called every frame
void ATP_LineCheckBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_LineCheckBox::ShiftBlock()
{
	if (BlockShiftAmount != 0 && !bNeedDeleteBlock)
	{
		UE_LOG(LogLineCheckBox, Display, TEXT("=======OnShiftBlock======="));
		UE_LOG(LogLineCheckBox, Display, TEXT("BoxIndex %i"), BoxIndex);
		UE_LOG(LogLineCheckBox, Display, TEXT("BlockShiftAmount is %i"), BlockShiftAmount);
		UE_LOG(LogLineCheckBox, Display, TEXT("bNeedDeleteBlock is %s"), bNeedDeleteBlock ? TEXT("TRUE") : TEXT("FALSE"));

		UE_LOG(LogLineCheckBox, Display, TEXT("Need to shift block"));

		//SingleBLock->SetBLockIndex(BoxIndex);
		SingleBLock->ShiftBlock(BlockShiftAmount);
		
		BlockShiftAmount = 0;
		SingleBLock = nullptr;
		bNeedDeleteBlock = false;
		bIsFulled = false;
	}
}

void ATP_LineCheckBox::DeleteBlock()
{
	if (bNeedDeleteBlock && BlockShiftAmount == 0)
	{
		UE_LOG(LogLineCheckBox, Display, TEXT("=======OnDeleteBlock======="));
		UE_LOG(LogLineCheckBox, Display, TEXT("BoxIndex %i"), BoxIndex);
		UE_LOG(LogLineCheckBox, Display, TEXT("BlockShiftAmount is %i"), BlockShiftAmount);
		UE_LOG(LogLineCheckBox, Display, TEXT("bNeedDeleteBlock is %s"), bNeedDeleteBlock ? TEXT("TRUE") : TEXT("FALSE"));

		UE_LOG(LogLineCheckBox, Display, TEXT("Yes, Need delete line"));

		SingleBLock->DeleteBlock();
		DestroyNiagaraComponent->SetAsset(DestroyNiagaraEffect, false);
		DestroyNiagaraComponent->SetActive(true, true);
		GetWorldTimerManager().SetTimer(DestroyBlockTimer, this, &ATP_LineCheckBox::DestroyBlock, TimeDestroyBlock, false);

		BlockShiftAmount = 0;
		SingleBLock = nullptr;
		bNeedDeleteBlock = false;
		bIsFulled = false;
	}
}

bool ATP_LineCheckBox::IsBlockOnSpot(const ATP_SingleBlock* Block) const
{
	return Block->GetNewBlockIndex() == BoxIndex ? true : false;
}

void ATP_LineCheckBox::DestroyBlock()
{
	GetWorldTimerManager().ClearTimer(DestroyBlockTimer);
	DestroyNiagaraComponent->SetActive(false, false);
}

