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

public:
	AInteractableDiagonalJump();
	
protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif

	UPROPERTY(EditAnywhere)
	float ImpulseStrength = 700.f;

	UPROPERTY(EditAnywhere)
	float SimulatedMoveSpeed = 300.f;

	UPROPERTY(EditAnywhere)
	bool bRotateRight = true;

	void OnInteract(ABuilderBob* Bob) override;

};
