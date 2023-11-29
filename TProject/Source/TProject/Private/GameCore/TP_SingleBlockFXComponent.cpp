// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCore/TP_SingleBlockFXComponent.h"
#include "NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogSingleBlockFXComponent, All, All);

// Sets default values for this component's properties
UTP_SingleBlockFXComponent::UTP_SingleBlockFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTP_SingleBlockFXComponent::PlayDestroyFX(const FVector& Location)
{
	const auto DestroyFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
		DestroyNiagaraEffect,
		Location,
		FRotator::ZeroRotator);
}

void UTP_SingleBlockFXComponent::PlayShiftFX(const FVector& Location)
{
	const auto ShiftFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
		ShiftNiagaraEffect,
		Location,
		FRotator::ZeroRotator);
}