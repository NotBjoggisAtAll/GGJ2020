// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "InteractableReverse.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AInteractableReverse : public ABaseInteractable
{
	GENERATED_BODY()
	
protected:
	void OnInteract(ABuilderBob* Bob) override;
};	
