// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BuildController.generated.h"

/**
 *
 */
UCLASS()
class GGJ2020_API ABuildController : public APlayerController
{
	GENERATED_BODY()

protected:
	ABuildController();

	virtual void Tick(float DeltaTime) override;

};
