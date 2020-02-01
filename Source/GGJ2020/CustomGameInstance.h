// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

class UCustomSaveGame;

/**
 * 
 */
UCLASS()
class GGJ2020_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Save();

	UFUNCTION(BlueprintCallable)
	bool Load();

	UPROPERTY(BlueprintReadOnly)
	UCustomSaveGame* SaveGame;

private:
	FString SlotNameString = "SaveSlot";
	uint32 UserIndexInt32 = 0;
};
