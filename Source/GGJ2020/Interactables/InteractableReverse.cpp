// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableReverse.h"
#include "../BuilderBob.h"

void AInteractableReverse::OnInteract(ABuilderBob* Bob)
{
	Bob->bMoveRight = !Bob->bMoveRight;
}