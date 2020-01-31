// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCamera.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GGJ2020_API APlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	APlayerCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScrollSpeed = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinZoom = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxZoom = 2000.f;


protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp(float Value);
	void MoveRight(float Value);
	void Zoom(float Value);




};
