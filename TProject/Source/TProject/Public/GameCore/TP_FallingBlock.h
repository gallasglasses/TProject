// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "TP_FallingBlock.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;

class ATP_SingleBlock;

UENUM(BlueprintType)
enum class ETPBlockShape : uint8
{
	O_block = 0,
	I_block,
	S_block,
	Z_block,
	L_block,
	J_block,
	T_block

};

UCLASS()
class TPROJECT_API ATP_FallingBlock : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_FallingBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components")
		USceneComponent* DefaultScene;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		UStaticMeshComponent* Cube1;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		UStaticMeshComponent* Cube2;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		UStaticMeshComponent* Cube3;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		UStaticMeshComponent* Cube4;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		FVector SpawnNewFallingBlockLocation = FVector(0.f, 0.f, 1000.f);

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components | Meshes")
		float CubeHeight = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ATP_SingleBlock> SingleBlockClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ATP_FallingBlock> NewFallingBlockClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cube | Color")
		TMap<ETPBlockShape, FLinearColor> BlockColors{
			{ ETPBlockShape::O_block, FLinearColor(FVector(1.f, 1.f, 0.f)) },
			{ ETPBlockShape::I_block, FLinearColor(FVector(0.f, 0.f, 1.f)) },
			{ ETPBlockShape::S_block, FLinearColor(FVector(1.f, 0.f, 0.f)) },
			{ ETPBlockShape::Z_block, FLinearColor(FVector(0.f, 1.f, 0.f)) },
			{ ETPBlockShape::L_block, FLinearColor(FVector(1.f, 0.1f, 0.f)) },
			{ ETPBlockShape::J_block, FLinearColor(FVector(1.f, 0.05f, 0.6f)) },
			{ ETPBlockShape::T_block, FLinearColor(FVector(0.1f, 0.f, 0.5f)) }
		};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cube | Number")
		TMap<int, ETPBlockShape> BlockNumbers{
			{ 0, ETPBlockShape::O_block },
			{ 1, ETPBlockShape::I_block },
			{ 2, ETPBlockShape::S_block },
			{ 3, ETPBlockShape::Z_block },
			{ 4, ETPBlockShape::L_block },
			{ 5, ETPBlockShape::J_block },
			{ 6, ETPBlockShape::T_block }
		};
	
	const FString CubeMeshPath = "/Script/Engine.StaticMesh'/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01'";

#pragma region /** Input */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		class UInputMappingContext* InputMapping;

#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Allows a Pawn to set up custom input bindings. Called upon possession by a PlayerController, using the InputComponent created by CreatePlayerInputComponent(). */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const struct FInputActionValue& ActionValue);

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
		float MoveScale;

	void Rotate();
	void Speed();
	void MoveLeft();
	void MoveRight();

private:

	FTimerHandle DropingBlockTimer;
	FLinearColor BlockColor;
	float TimeToDropBlock = 0.5f;
	bool bShouldDrop = false;

	void DropBlock();
};
