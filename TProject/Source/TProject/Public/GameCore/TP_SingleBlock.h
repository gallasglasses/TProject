// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_SingleBlock.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components | VFX")
		UNiagaraComponent* DestroyNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components | VFX")
		UNiagaraSystem* DestroyNiagaraEffect;

	const FString DestroyNiagaraEffectPath = "Niagara.NiagaraSystem'/Game/TProjectContent/FX/NS_DestroyCubeFX.NS_DestroyCubeFX'";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components | VFX")
		UNiagaraComponent* ShiftNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components | VFX")
		UNiagaraSystem* ShiftNiagaraEffect;

	UPROPERTY(EditAnywhere, Category = "LineBox")
		int32 BlockIndex;

	const FString ShiftNiagaraEffectPath = "Niagara.NiagaraSystem'/Game/TProjectContent/FX/NS_ShiftCubeFX.NS_ShiftCubeFX'";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBLockIndex(const int32& Index) { BlockIndex = Index; };
	void SetBlockColor(const FLinearColor& Color) { BlockColor = Color; }
	void ShiftBlock(const int32& Amount);
	void OnShiftBlock();
	void DeleteBlock();

	int32 GetBlockIndex() const { return BlockIndex; };
	int32 GetNewBlockIndex() const;
	bool IsShiftingBlock() const { return ShiftAmountBlock != 0 ? true : false;};

private:

	void DestroyBlock();

	FLinearColor BlockColor = FLinearColor::White;

	FTimerHandle ShiftBlockTimer;
	FTimerHandle DestroyBlockTimer;

	//int32 BlockIndex;
	int32 ShiftAmountBlock;

	float CalculatedShiftAmountBlock = 0;
	float TimeShiftBlock = 0.02f;
	float TimeDestroyBlock = 0.5f;
	float AlphaShiftBlock = 0.05f;
};
