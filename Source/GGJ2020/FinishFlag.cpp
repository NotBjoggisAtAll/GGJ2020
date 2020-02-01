// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishFlag.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


AFinishFlag::AFinishFlag()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);

	Collision->SetGenerateOverlapEvents(true);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}



