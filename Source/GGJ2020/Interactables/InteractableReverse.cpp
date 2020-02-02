// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableReverse.h"
#include "../BuilderBob.h"
#include "Components/PrimitiveComponent.h"
void AInteractableReverse::OnInteract(ABuilderBob* Bob)
{
	Super::OnInteract(Bob);
	Bob->SwapMoveDirection();
	
	auto comp = Cast<UPrimitiveComponent>(Bob->GetRootComponent());
	if (comp->IsSimulatingPhysics())
	{
		comp->SetPhysicsLinearVelocity(FVector::ZeroVector);
	}
}