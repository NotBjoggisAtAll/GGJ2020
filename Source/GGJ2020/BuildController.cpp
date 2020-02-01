// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildController.h"
#include "Interactables/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"
#include "CameraPawn.h"

ABuildController::ABuildController()
{
}

void ABuildController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

	SpawnInteractable();

	ControllingPawn = Cast<ACameraPawn>(GetPawn());
	
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
			GridSnapLocation = GetGridLocation();
			if (FVector::Dist(CurrentInteractable->GetActorLocation(), GetGridLocation()) > GridSize * 2)
			{
				CurrentInteractable->SetActorLocation(ControllingPawn->IsMoving() ? GetMouseLocation() : GetGridLocation());
				Beam = nullptr;
				CurrentInteractable->SetMaterial(EMaterialType::Default);
			}
			else {

				if (FMath::Abs(Beam->GetActorRotation().Pitch) == 0) //Horizontal
				{
					GridSnapLocation.Z = Beam->GetActorLocation().Z;
					CurrentInteractable->SetActorLocation(ControllingPawn->IsMoving() ? GetMouseLocation() : GridSnapLocation);
				}
				else //Vertical
				{
					GridSnapLocation.X = Beam->GetActorLocation().X;
					CurrentInteractable->SetActorLocation(ControllingPawn->IsMoving() ? GetMouseLocation() : GridSnapLocation);
				}
			}
		}
		else
		{
			CurrentInteractable->SetActorLocation(ControllingPawn->IsMoving() ? GetMouseLocation() : GetGridLocation());
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
			CurrentInteractable->SetActorLocation(GridSnapLocation);
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

		OnScroll.Broadcast(InteractIndex);
		SpawnInteractable();
	}
}

FVector ABuildController::GetMouseLocation()
{
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);
	FVector Location = HitResult.Location;
	Location.Y = 0;
	return Location;
}

FVector ABuildController::GetGridLocation()
{
	FVector Location = GetMouseLocation();

	Location.X = FMath::RoundToFloat(Location.X / GridSize) * GridSize;
	Location.Z = FMath::RoundToFloat(Location.Z / GridSize) * GridSize;

	return Location;
}