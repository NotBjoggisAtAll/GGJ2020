// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

class UBoxComponent;

UCLASS()
class GGJ2020_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectible();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void SetCollected();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* TakenMaterial;

	UPROPERTY(EditDefaultsOnly)
	FRotator Rotation = FRotator(50.f, 0, 0);

};
