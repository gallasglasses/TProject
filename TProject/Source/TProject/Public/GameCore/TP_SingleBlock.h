// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_SingleBlock.generated.h"

UCLASS()
class TPROJECT_API ATP_SingleBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_SingleBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		UStaticMeshComponent* Cube;

	const FString CubeMeshPath = "/Script/Engine.StaticMesh'/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01'";

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		float CubeHeight = 50.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBlockColor(const FLinearColor& Color) { BlockColor = Color; }
	void ShiftBlock(const int& Amount);

private:

	FLinearColor BlockColor;

};
