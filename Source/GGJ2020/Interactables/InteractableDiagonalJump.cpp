// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDiagonalJump.h"
#include "../BuilderBob.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"


void AInteractableDiagonalJump::OnInteract(ABuilderBob* Bob)
{
	auto comp = Cast<UPrimitiveComponent>(Bob->GetRootComponent());
	comp->SetSimulatePhysics(true);

	comp->SetPhysicsLinearVelocity(FVector::ZeroVector);

	comp->SetConstraintMode(EDOFMode::XZPlane);
	comp->AddImpulse(GetActorUpVector() * ImpulseStrength, NAME_None);

	Bob->bMoveRight = !Bob->bMoveRight;
}
