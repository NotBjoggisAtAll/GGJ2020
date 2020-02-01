// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "CustomSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UCustomGameInstance::Save()
{
    if (auto SaveGameInstance = Cast<UCustomSaveGame>(UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass())))
    {
        // Set data on the savegame object.
        

        // Save the data immediately.
        if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotNameString, UserIndexInt32))
        {
            UE_LOG(LogTemp, Warning, TEXT("Saved successfully"));
        }
    }
}

bool UCustomGameInstance::Load()
{
    // Retrieve and cast the USaveGame object to UMySaveGame.
    SaveGame = Cast<UCustomSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotNameString, UserIndexInt32));

    if(SaveGame)
    {
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        UE_LOG(LogTemp, Warning, TEXT("Loaded Successfully"));

        return true;
    }

    return false;
}