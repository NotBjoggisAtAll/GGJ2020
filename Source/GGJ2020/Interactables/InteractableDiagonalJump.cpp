// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDiagonalJump.h"
#include "../BuilderBob.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"

AInteractableDiagonalJump::AInteractableDiagonalJump()
{

}

void AInteractableDiagonalJump::OnInteract(ABuilderBob* Bob)
{
	auto comp = Cast<UPrimitiveComponent>(Bob->GetRootComponent());

	comp->SetSimulatePhysics(true);

	Bob->SetMoveDirection(bRotateRight);

	auto xVel = (bRotateRight) ? SimulatedMoveSpeed : -SimulatedMoveSpeed;
	comp->SetPhysicsLinearVelocity({ xVel, 0, 0 });

	comp->AddImpulse(GetActorUpVector() * ImpulseStrength, NAME_None, true);
}

#if WITH_EDITOR
void AInteractableDiagonalJump::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == NAME_None)
		return;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AInteractableDiagonalJump, bRotateRight)))
	{
		SetActorRotation(FRotator((bRotateRight) ? -45.f : 45.f, 0, 0));
	}
}
#endif