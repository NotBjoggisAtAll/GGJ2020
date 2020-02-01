// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

class ABuilderBob;
class UBoxComponent;

UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	Default UMETA(DisplayName  ="Default"), 
	CanPlace  UMETA(DisplayName = "Can Place"),
	CanNotPlace UMETA(DisplayName = "Can Not Place")
};

UCLASS()
class GGJ2020_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseInteractable();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintImplementableEvent)
	void SetMaterial(EMaterialType MaterialType);

protected:
	virtual void OnInteract(ABuilderBob* Bob);


private:


	UFUNCTION()
	void OnInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
