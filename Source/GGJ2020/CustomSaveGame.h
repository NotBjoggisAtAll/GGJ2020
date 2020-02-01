// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomSaveGame.generated.h"


USTRUCT(BlueprintType)
struct FLevelData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int> Collected;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Max;
};
/**
 * 
 */
UCLASS()
class GGJ2020_API UCustomSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UCustomSaveGame();

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
    TArray<FLevelData> Levels;
    
};
