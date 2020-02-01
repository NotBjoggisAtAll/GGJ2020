// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "InteractableDiagonalJump.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AInteractableDiagonalJump : public ABaseInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	float ImpulseStrength = 700.f;

	void OnInteract(ABuilderBob* Bob) override;

};
