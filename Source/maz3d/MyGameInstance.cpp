




// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::hostGame()
{

	FVector vector(0);
	FRotator rotator(0);
	connection = (ATcpConnection*)GetWorld()->SpawnActor(ATcpConnection::StaticClass(), &vector, &rotator);
	connection->ConnectToGameServer();
}