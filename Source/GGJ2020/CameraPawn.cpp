// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->SetupAttachment(Scene);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(0, -90, 0));

}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &ACameraPawn::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACameraPawn::MoveRight);
	PlayerInputComponent->BindAxis("Zoom", this, &ACameraPawn::Zoom);

}

void ACameraPawn::MoveUp(float Value)
{
	if (Value != 0)
	{
		AddActorWorldOffset(FVector(0, 0, 1) * MovementSpeed * Value);
	}
}

void ACameraPawn::MoveRight(float Value)
{
	if (Value != 0)
	{
		AddActorWorldOffset(FVector(1, 0, 0) * MovementSpeed * Value);
	}
}

void ACameraPawn::Zoom(float Value)
{
	if (Value != 0)
	{
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - Value * ScrollSpeed, MinZoom, MaxZoom);
	}
}

