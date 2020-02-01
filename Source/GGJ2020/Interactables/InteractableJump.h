// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "InteractableJump.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AInteractableJump : public ABaseInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	float ImpulseStrength = 700.f;

	UPROPERTY(EditAnywhere)
	float SimulatedMoveSpeed = 800.f;

	void OnInteract(ABuilderBob* Bob) override;
};
