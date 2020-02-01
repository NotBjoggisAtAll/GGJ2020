// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSawblade.h"
#include "Components/StaticMeshComponent.h"
#include "BuilderBob.h"
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

void AInteractableSawblade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Sawblade->AddLocalRotation(FRotator(SawbladeRotationSpeed * DeltaTime, 0, 0));
}
