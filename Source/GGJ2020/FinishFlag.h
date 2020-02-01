// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishFlag.generated.h"

class UBoxComponent;

UCLASS()
class GGJ2020_API AFinishFlag : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishFlag();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

};
