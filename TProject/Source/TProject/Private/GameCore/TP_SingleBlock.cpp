// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_SingleBlock.h"

// Sets default values
ATP_SingleBlock::ATP_SingleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	SetRootComponent(Cube);
	Cube->SetCollisionProfileName("BlockAll");
	//Cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Cube->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	UStaticMesh* CubeMeshTemp = LoadObject<UStaticMesh>(this, *CubeMeshPath);
	if (CubeMeshTemp)
	{
		Cube->SetStaticMesh(CubeMeshTemp);
	}
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

