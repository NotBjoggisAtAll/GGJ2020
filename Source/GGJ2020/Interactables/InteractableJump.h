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
	UPROPERTY(EditDefaultsOnly)
	float ImpulseStrength = 1000.f;

	void OnInteract(ABuilderBob* Bob);
};
