// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ACollectible::ACollectible()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);
}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectible::SetCollected()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if(TakenMaterial)
		Mesh->SetMaterial(0, TakenMaterial);
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(Rotation * DeltaTime);
}

