// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableJump.h"
#include "../BuilderBob.h"
#include "Components/PrimitiveComponent.h"

void AInteractableJump::OnInteract(ABuilderBob* Bob)
{
	auto comp = Cast<UPrimitiveComponent>(Bob->GetRootComponent());
	comp->SetSimulatePhysics(true);
	comp->SetConstraintMode(EDOFMode::XZPlane);
	comp->AddImpulse({ 0, 0, ImpulseStrength }, NAME_None, true);
}