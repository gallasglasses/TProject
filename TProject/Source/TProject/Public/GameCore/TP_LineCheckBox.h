// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_LineCheckBox.generated.h"

class UBoxComponent;
class USceneComponent;
class ATP_SingleBlock;
class UParticleSystem;

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

	UPROPERTY(EditDefaultsOnly, Category = "LineBox")
		UParticleSystem* ExplosionEmitter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LineBox")
		FVector BoxExtent = FVector(5.f, 5.f, 5.f);

	UPROPERTY(EditAnywhere, Category = "LineBox")
		int BoxIndex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//FOnBoxFulledSignature OnBoxFulled;
	//FOnDeletedBlockSignature OnDeletedBlock;

	void ShiftBlock();
	void DeleteBlock();

	void SetBoxIndex(const int& Index) { BoxIndex = Index; };
	void SetShiftAmount(const int& Amount) { BlockShiftAmount = Amount; };
	void SetNeedDelete(const bool& NeedDeleteBlock) { bNeedDeleteBlock = NeedDeleteBlock; };

	const int& GetBoxIndex() const { return BoxIndex; };
	const bool& GetIsFulled() const { return bIsFulled; };

private:

	ATP_SingleBlock* SingleBLock;

	int BlockShiftAmount = 0;

	bool bNeedDeleteBlock = false;
	bool bIsFulled = false;

};
