// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCamera.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerCamera::APlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->SetupAttachment(Scene);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &APlayerCamera::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCamera::MoveRight);
	PlayerInputComponent->BindAxis("Zoom", this, &APlayerCamera::Zoom);

}

void APlayerCamera::MoveUp(float Value)
{
	if (Value != 0)
	{
		AddActorWorldOffset(FVector(0, 0, 1) * MovementSpeed * Value);
	}
}

void APlayerCamera::MoveRight(float Value)
{
	if (Value != 0)
	{
		AddActorWorldOffset(FVector(1, 0, 0) * MovementSpeed * Value);
	}
}

void APlayerCamera::Zoom(float Value)
{
	if (Value != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - Value * ScrollSpeed ,MinZoom, MaxZoom);
	}
}
