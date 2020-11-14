// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TcpConnection.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAZ3D_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

    ATcpConnection* connection;

    UFUNCTION(BlueprintCallable)
    void hostGame();

public:
    int playerCount;
};
