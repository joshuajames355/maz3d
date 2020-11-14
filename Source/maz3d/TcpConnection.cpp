// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpConnection.h"

ATcpConnection::ATcpConnection()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bAllowTickBeforeBeginPlay = true;
	SetActorTickEnabled(true);
}

void ATcpConnection::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveFromRoot();
}

void ATcpConnection::ConnectToGameServer() {
	if (isConnected(connectionIdGameServer))
	{
		UE_LOG(LogTemp, Log, TEXT("Log: Can't connect SECOND time. We're already connected!"));
		return;
	}
	FTcpSocketDisconnectDelegate disconnectDelegate;
	disconnectDelegate.BindDynamic(this, &ATcpConnection::OnDisconnected);
	FTcpSocketConnectDelegate connectDelegate;
	connectDelegate.BindDynamic(this, &ATcpConnection::OnConnected);
	FTcpSocketReceivedMessageDelegate receivedDelegate;
	receivedDelegate.BindDynamic(this, &ATcpConnection::OnMessageReceived);
	Connect("127.0.0.1", 46920, disconnectDelegate, connectDelegate, receivedDelegate, connectionIdGameServer);
	waitingForPC = false;
	conid = -1;
}

void ATcpConnection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!waitingForPC && conid != -1)
	{
		UE_LOG(LogTemp, Log, TEXT("SEND"));
		TArray<uint8> data;
		data.AddZeroed(3);
		FString string = "?PC";


		memcpy(&data, TCHAR_TO_ANSI(*string), 3);
		SendData(conid, data);

		waitingForPC = true;
	}
}

void ATcpConnection::OnConnected(int32 ConId) {
	UE_LOG(LogTemp, Log, TEXT("Log: Connected to server. %d"), ConId);
	conid = ConId;
}


void ATcpConnection::OnDisconnected(int32 ConId) {
	UE_LOG(LogTemp, Log, TEXT("Log: OnDisconnected."));
	conid = -1;
}

void ATcpConnection::OnMessageReceived(int32 ConId, TArray<uint8>& Message) {
	UE_LOG(LogTemp, Log, TEXT("Log: Received message."));
	// In this example, we always encode messages a certain way:
	// The first 4 bytes contain the length of the rest of the message.
	while (Message.Num() != 0) {
		// read expected length
		int32 msgLength = Message_ReadInt(Message);
		if (msgLength == -1) // when we can't read 4 bytes, the method returns -1
			return;
		TArray<uint8> yourMessage;
		// read the message itself
		if (!Message_ReadBytes(msgLength, Message, yourMessage)) {
			// If it couldn't read expected number of bytes, something went wrong.
			// Print a UE_LOG here, while your project is in development.
			continue;
		}
		// If the message was read, then treat "yourMessage" here!
		// ...
		// And then we go back to the "while", because we may have received multiple messages in a frame, 
		// so they all have to be read.
	}
}