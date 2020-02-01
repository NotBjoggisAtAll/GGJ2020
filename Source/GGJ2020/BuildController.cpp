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

	if (BP_Interactables.Num())
	{
		CurrentInteractable = GetWorld()->SpawnActor<ABaseInteractable>(BP_Interactables[InteractIndex], GetGridLocation(), FRotator(0, 0, 0));
		CurrentInteractable->Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
				//Set red material
			}
			else {
				//Set green material
			}
			Beam = BeamActors[0];
			FVector Grid = GetGridLocation();
			if (FVector::Dist(CurrentInteractable->GetActorLocation(), GetGridLocation()) > GridSize * 2)
			{
				CurrentInteractable->SetActorLocation(GetGridLocation());
				Beam = nullptr;
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
			CurrentInteractable = nullptr;
			Beam = nullptr;
			CurrentInteractable = GetWorld()->SpawnActor<ABaseInteractable>(BP_Interactables[InteractIndex], GetGridLocation(), FRotator(0, 0, 0));
			CurrentInteractable->Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

		CurrentInteractable = GetWorld()->SpawnActor<ABaseInteractable>(BP_Interactables[InteractIndex], GetGridLocation(), FRotator(0, 0, 0));
		CurrentInteractable->Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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