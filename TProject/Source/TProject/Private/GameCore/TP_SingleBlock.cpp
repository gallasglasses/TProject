// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_SingleBlock.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSingleBlock, All, All);

// Sets default values
ATP_SingleBlock::ATP_SingleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	SetRootComponent(Cube);
	Cube->SetCollisionProfileName("BlockAll");

	UStaticMesh* CubeMeshTemp = LoadObject<UStaticMesh>(this, *CubeMeshPath);
	if (CubeMeshTemp)
	{
		Cube->SetStaticMesh(CubeMeshTemp);
	}

	ShiftNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("ShiftNiagaraComponent");
	ShiftNiagaraComponent->SetupAttachment(Cube);

	ShiftNiagaraEffect = LoadObject<UNiagaraSystem>(this, *ShiftNiagaraEffectPath);

	/*DestroyNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("DestroyNiagaraComponent");
	DestroyNiagaraComponent->SetupAttachment(Cube);

	DestroyNiagaraEffect = LoadObject<UNiagaraSystem>(this, *DestroyNiagaraEffectPath);*/
}

// Called when the game starts or when spawned
void ATP_SingleBlock::BeginPlay()
{
	Super::BeginPlay();

	Cube->SetVectorParameterValueOnMaterials("GlowColor", FVector(BlockColor));
}

// Called every frame
void ATP_SingleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATP_SingleBlock::ShiftBlock(const int32& Amount)
{
	ShiftNiagaraComponent->SetAsset(ShiftNiagaraEffect, false);
	ShiftNiagaraComponent->SetActive(true, true);

	ShiftAmountBlock = Amount;
	/*CalculatedShiftAmountBlock = -Amount * CubeHeight;
	AddActorWorldOffset(FVector(0.f, 0.f, -Amount * CubeHeight));*/

	// for smooth shift, but it work bad with notify overlap on shift:
	// 
	CalculatedShiftAmountBlock = GetActorLocation().Z - Amount * CubeHeight;

	//UE_LOG(LogSingleBlock, Display, TEXT("GetActorLocation %s"), *GetActorLocation().ToString());
	UE_LOG(LogSingleBlock, Display, TEXT("CalculatedShiftAmountBlock %f"), CalculatedShiftAmountBlock);

	GetWorldTimerManager().SetTimer(ShiftBlockTimer, this, &ATP_SingleBlock::OnShiftBlock, TimeShiftBlock, true);

}

void ATP_SingleBlock::OnShiftBlock()
{
	if (!FMath::IsNearlyEqual(CalculatedShiftAmountBlock, GetActorLocation().Z, 0.01))
	{
		FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, FMath::Lerp(GetActorLocation().Z, CalculatedShiftAmountBlock, AlphaShiftBlock));
		SetActorLocation(NewLocation);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ShiftBlockTimer);
		ShiftNiagaraComponent->SetActive(false, false);
		CalculatedShiftAmountBlock = 0.f;
		ShiftAmountBlock = 0;
	}
}

void ATP_SingleBlock::DeleteBlock()
{
	ShiftNiagaraComponent->SetActive(false, false);
	Cube->SetVisibility(false);
	//DestroyNiagaraComponent->SetAsset(DestroyNiagaraEffect, false);
	//DestroyNiagaraComponent->SetActive(true, true);

	GetWorldTimerManager().SetTimer(DestroyBlockTimer, this, &ATP_SingleBlock::DestroyBlock, TimeDestroyBlock, false);
}

int32 ATP_SingleBlock::GetNewBlockIndex() const
{
	return (BlockIndex / 10 - ShiftAmountBlock) * 10 + BlockIndex % 10;
}

void ATP_SingleBlock::DestroyBlock()
{
	GetWorldTimerManager().ClearTimer(DestroyBlockTimer);
	Destroy();
}

