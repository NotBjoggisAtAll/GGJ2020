// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSawblade.h"
#include "Components/StaticMeshComponent.h"
#include "BuilderBob.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AInteractableSawblade::AInteractableSawblade()
{
	Sawblade = CreateDefaultSubobject<UStaticMeshComponent>("Sawblade");
	Sawblade->SetupAttachment(RootComponent);

	Sawblade->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractableSawblade::OnInteract(ABuilderBob* Bob)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void AInteractableSawblade::BeginPlay()
{
	Super::BeginPlay();

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AInteractableSawblade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Sawblade->AddLocalRotation(FRotator(0, 0, SawbladeRotationSpeed * DeltaTime));
}
