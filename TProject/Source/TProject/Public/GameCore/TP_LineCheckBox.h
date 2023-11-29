// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_LineCheckBox.generated.h"

class UBoxComponent;
class USceneComponent;
class ATP_SingleBlock;

class UNiagaraSystem;
class UNiagaraComponent;

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnBoxFulledSignature, int);
//DECLARE_MULTICAST_DELEGATE(FOnDeletedBlockSignature);

UCLASS()
class TPROJECT_API ATP_LineCheckBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_LineCheckBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components")
		USceneComponent* DefaultScene;

	UPROPERTY(EditDeFaultsOnly, BlueprintReadWrite, category = "Components")
		UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, Category = "LineBox")
		TSubclassOf<ATP_SingleBlock> SingleBlockClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LineBox")
		FVector BoxExtent = FVector(5.f, 5.f, 5.f);

	UPROPERTY(EditAnywhere, Category = "LineBox")
		int32 BoxIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components | VFX")
		UNiagaraComponent* DestroyNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components | VFX")
		UNiagaraSystem* DestroyNiagaraEffect;

	const FString DestroyNiagaraEffectPath = "Niagara.NiagaraSystem'/Game/TProjectContent/FX/NS_DestroyCubeFX.NS_DestroyCubeFX'";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//FOnBoxFulledSignature OnBoxFulled;
	//FOnDeletedBlockSignature OnDeletedBlock;

	void ShiftBlock();
	void DeleteBlock();

	void SetBoxIndex(const int32& Index) { BoxIndex = Index; };
	void SetShiftAmount(const int32& Amount) { BlockShiftAmount = Amount; };
	void SetNeedDelete(const bool& NeedDeleteBlock) { bNeedDeleteBlock = NeedDeleteBlock; };

	const int32& GetBoxIndex() const { return BoxIndex; };
	const bool& GetIsFulled() const { return bIsFulled; };

	bool IsBlockOnSpot(const ATP_SingleBlock* Block) const;

private:

	void DestroyBlock();

	ATP_SingleBlock* SingleBLock;

	FTimerHandle DestroyBlockTimer;

	int32 BlockShiftAmount = 0;

	float TimeDestroyBlock = 5.f;

	bool bNeedDeleteBlock = false;
	bool bIsFulled = false;
};
