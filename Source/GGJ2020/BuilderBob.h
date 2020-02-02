// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BuilderBob.generated.h"

class ACollectible;

UCLASS()
class GGJ2020_API ABuilderBob : public ACharacter
{
	GENERATED_BODY()

public:
	ABuilderBob();

	void SwapMoveDirection();

	void SetMoveDirection(bool Value);

	bool GetMoveRight() const;


	UPROPERTY(BlueprintReadOnly)
	bool bSpeedBoost = false;

	UFUNCTION(BlueprintCallable)
	void OnCollected(ACollectible* Collectible);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
		bool bMoveRight = true;

	UPROPERTY(BlueprintReadOnly)
	TArray<ACollectible*> WorldCollectibles;

	UPROPERTY(BlueprintReadOnly)
	TArray<int> Collection;

};
