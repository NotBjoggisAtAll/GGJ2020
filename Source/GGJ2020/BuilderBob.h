// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BuilderBob.generated.h"

UCLASS()
class GGJ2020_API ABuilderBob : public ACharacter
{
	GENERATED_BODY()

public:
	ABuilderBob();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
