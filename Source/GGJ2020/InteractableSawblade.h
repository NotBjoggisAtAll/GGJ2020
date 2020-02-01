// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/BaseInteractable.h"
#include "InteractableSawblade.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AInteractableSawblade : public ABaseInteractable
{
	GENERATED_BODY()

public:
	AInteractableSawblade();
	
protected:

	void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float SawbladeRotationSpeed = 50.f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Sawblade;

	void OnInteract(ABuilderBob* Bob) override;
};
