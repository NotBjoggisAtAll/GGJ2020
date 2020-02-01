// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildController.h"
#include "Interactables/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"

ABuildController::ABuildController()
{
	bShowMouseCursor = true;

}

void ABuildController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

	SpawnInteractable();

}

void ABuildController::SpawnInteractable()
{
	if (BP_Interactables.Num())
	{
		CurrentInteractable = GetWorld()->SpawnActor<ABaseInteractable>(BP_Interactables[InteractIndex], GetGridLocation(), FRotator(0, 0, 0));
	}
}

void ABuildController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent != nullptr);

	InputComponent->BindAction("Place", EInputEvent::IE_Pressed, this, &ABuildController::OnLeftClicked);
	InputComponent->BindAction("Remove", EInputEvent::IE_Pressed, this, &ABuildController::OnRightClicked);

	InputComponent->BindAxis("CycleInteractables", this, &ABuildController::CycleInteractables);
}

void ABuildController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentInteractable)
	{

		TArray<AActor*> BeamActors;
		CurrentInteractable->GetOverlappingActors(BeamActors, BP_RedBeam);
		if (BeamActors.Num() != 0)
		{
			TArray<AActor*> AllInteractables;
			CurrentInteractable->GetOverlappingActors(AllInteractables, ABaseInteractable::StaticClass());
			if (AllInteractables.Num() == 0)
			{
				CurrentInteractable->SetMaterial(EMaterialType::CanPlace);
			}
			else {
				CurrentInteractable->SetMaterial(EMaterialType::CanNotPlace);
			}
			Beam = BeamActors[0];
			FVector Grid = GetGridLocation();
			if (FVector::Dist(CurrentInteractable->GetActorLocation(), GetGridLocation()) > GridSize * 2)
			{
				CurrentInteractable->SetActorLocation(GetGridLocation());
				Beam = nullptr;
				CurrentInteractable->SetMaterial(EMaterialType::Default);
			}
			else {

				if (FMath::Abs(Beam->GetActorRotation().Pitch) == 0) //Horizontal
				{
					Grid.Z = Beam->GetActorLocation().Z;
					CurrentInteractable->SetActorLocation(Grid);
				}
				else //Vertical
				{
					Grid.X = Beam->GetActorLocation().X;
					CurrentInteractable->SetActorLocation(Grid);
				}
			}
		}
		else
		{
			CurrentInteractable->SetActorLocation(GetGridLocation());
			Beam = nullptr;
			CurrentInteractable->SetMaterial(EMaterialType::Default);
		}
	}
}

void ABuildController::OnLeftClicked()
{
	if (Beam)
	{
		TArray<AActor*> AllInteractables;
		CurrentInteractable->GetOverlappingActors(AllInteractables, ABaseInteractable::StaticClass());
		if (AllInteractables.Num() == 0)
		{
			CurrentInteractable->Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			CurrentInteractable->SetMaterial(EMaterialType::Default);
			CurrentInteractable = nullptr;
			Beam = nullptr;
			SpawnInteractable();
		}
	}
}

void ABuildController::OnRightClicked()
{
	TArray<AActor*> AllInteractables;
	CurrentInteractable->GetOverlappingActors(AllInteractables, ABaseInteractable::StaticClass());
	for (auto& Interactable : AllInteractables)
		Interactable->Destroy();

}

void ABuildController::CycleInteractables(float Value)
{
	if (Value == 0)
		return;

	if (CurrentInteractable)
	{
		CurrentInteractable->Destroy();
		if (Value > 0)
			InteractIndex = (InteractIndex + 1) % BP_Interactables.Num();
		else
			InteractIndex = (InteractIndex ? InteractIndex : BP_Interactables.Num()) - 1;

		SpawnInteractable();
	}
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