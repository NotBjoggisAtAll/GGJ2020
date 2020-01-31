// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "../BuilderBob.h"

ABaseInteractable::ABaseInteractable()
{

	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractable::OnInteractOverlap);
}

void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInteractable::OnInteract(ABuilderBob* Bob)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted"));
}

void ABaseInteractable::OnInteractOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABuilderBob::StaticClass()))
	{
		OnInteract(Cast<ABuilderBob>(OtherActor));
	}
}

