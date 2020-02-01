// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildController.h"
#include "Interactables/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"

ABuildController::ABuildController()
{
	bShowMouseCursor = true;
	
}

void ABuildController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

//	CurrentInteractable = GetWorld()->SpawnActor<ABaseInteractable>(BP_CurrentInteractable, GetGridLocation(), FRotator(0,0,0));
	//CurrentInteractable->Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void ABuildController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent != nullptr);

	InputComponent->BindAction("Place", EInputEvent::IE_Pressed, this, &ABuildController::OnMouseClicked);
}

void ABuildController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentInteractable)
		CurrentInteractable->SetActorLocation(GetGridLocation());
}

void ABuildController::OnMouseClicked()
{

	TArray<AActor*> Actors;
	CurrentInteractable->GetOverlappingActors(Actors, BP_RedBeam);

	for(const auto& Actor : Actors)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetNameSafe(Actor));

	//CurrentInteractable->Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CurrentInteractable = nullptr;
}

FVector ABuildController::GetGridLocation()
{
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);
	FVector Location = HitResult.Location;

	Location.X = FMath::RoundToFloat(Location.X / GridSize) * GridSize;
	Location.Y = 0;
	Location.Z = FMath::RoundToFloat(Location.Z / GridSize) * GridSize;

	return Location;
}