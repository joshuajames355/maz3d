// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TcpSocketConnection.h"
#include <string>
#include "TcpConnection.generated.h"

/**
 * 
 */
UCLASS()
class MAZ3D_API ATcpConnection : public ATcpSocketConnection
{
	GENERATED_BODY()

	bool waitingForPC;
	int32 conid;
public:
	ATcpConnection();

	UFUNCTION()
		void OnConnected(int32 ConnectionId);

	UFUNCTION()
		void OnDisconnected(int32 ConId);

	UFUNCTION()
		void OnMessageReceived(int32 ConId, TArray<uint8>& Message);

	UFUNCTION(BlueprintCallable)
		void ConnectToGameServer();

	UPROPERTY()
		int32 connectionIdGameServer;

	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
