// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ACollectible::ACollectible()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);
}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	AddActorLocalRotation(FRotator(-50.f * DeltaTime, 0, 0));
}

