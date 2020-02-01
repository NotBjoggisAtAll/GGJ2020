// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BuildController.generated.h"

class ABaseInteractable;

UCLASS()
class GGJ2020_API ABuildController : public APlayerController
{
	GENERATED_BODY()

protected:
	ABuildController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	FVector GetGridLocation();
	FHitResult HitResult;

	void OnMouseClicked();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseInteractable> BP_CurrentInteractable;

	float GridSize = 100.f;

	ABaseInteractable* CurrentInteractable = nullptr;

};
