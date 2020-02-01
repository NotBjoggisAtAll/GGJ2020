// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableJump.h"
#include "../BuilderBob.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AInteractableJump::OnInteract(ABuilderBob* Bob)
{
	auto comp = Cast<UPrimitiveComponent>(Bob->GetRootComponent());
	comp->SetSimulatePhysics(true);
	comp->SetConstraintMode(EDOFMode::XZPlane);

	auto xVel = (Bob->bMoveRight) ? 600 : -600;

	comp->SetPhysicsLinearVelocity(FVector(xVel, 0, 0));
	comp->AddImpulse(GetActorUpVector() * ImpulseStrength, NAME_None, true);
}