// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Json.h"
#include "MapGeneratorGamemode.generated.h"


USTRUCT(BlueprintType)
struct FLevela
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<bool> points;
};

USTRUCT(BlueprintType)
struct FPortalStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		int maze;
	UPROPERTY(BlueprintReadWrite)
		int x;
	UPROPERTY(BlueprintReadWrite)
		int y;
	UPROPERTY(BlueprintReadWrite)
		int rot;
};

USTRUCT(BlueprintType)
struct FPortalPair
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		FPortalStruct in;
	UPROPERTY(BlueprintReadWrite)
		FPortalStruct out;
};

USTRUCT(BlueprintType)
struct FMapStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FLevela> floors;

	UPROPERTY(BlueprintReadWrite)
	TArray<FPortalPair> portals;
};

/**
 * 
 */
UCLASS()
class MAZ3D_API AMapGeneratorGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintImplementableEvent)
	//void generateMap(TArray<FLevela> map);

	UFUNCTION(BlueprintCallable)
	FMapStruct decodeMap(const FString& map);
};
