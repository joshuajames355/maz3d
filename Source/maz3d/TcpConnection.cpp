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
	if (conid != -1)
	{
		Disconnect(conid);
	}
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
	Connect("192.168.1.171", 46920, disconnectDelegate, connectDelegate, receivedDelegate, connectionIdGameServer);
	waitingForPC = false;
	conid = -1;
	pc = 0;
}

TArray<uint8> toArray(FString string)
{
	TArray<uint8> test = TArray<uint8>();
	for (int x = 0; x < string.Len(); x++)
	{
		test.Add(string[x]);
	}
	return test;
}

FString fromArray(TArray<uint8> data)
{
	FString test = "";
	for (int x = 0; x < data.Num(); x++)
	{
		test += char(data[x]);
	}
	return test;
}

void ATcpConnection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!waitingForPC && conid != -1)
	{
		UE_LOG(LogTemp, Log, TEXT("SEND"));
		SendData(conid, toArray("?$"));
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

		FString message = "";
		uint8 byte = Message_ReadByte(Message);
		while (byte != '$')
		{
			message += char(byte);
			byte = Message_ReadByte(Message);
		}

		if (message.StartsWith("?"))
		{
			FString split = message.RightChop(1);
			UE_LOG(LogTemp, Log, TEXT("split %s"), *split);
			pc = FCString::Atoi(*split);
			waitingForPC = false;
		}

		UE_LOG(LogTemp, Log, TEXT("message %s") , *message);

		// If the message was read, then treat "yourMessage" here!
		// ...
		// And then we go back to the "while", because we may have received multiple messages in a frame, 
		// so they all have to be read.
	}
}

void ATcpConnection::sendPosition(float x, float y, float z, float angle)
{
	if(conid != -1)
	{
		FString data = "#{\"x\":" + FString::SanitizeFloat(x) + ", \"y\" : " + FString::SanitizeFloat(y) + ",\"world\" : " + FString::SanitizeFloat(z) + ", \"rotation\": " + FString::SanitizeFloat(angle) + "}$";
		SendData(conid, toArray(data));
	}
}

void ATcpConnection::sendString(FString data)
{
	if (conid != -1)
	{
		SendData(conid, toArray(data));
	}
}

void ATcpConnection::sendMap(FString map)
{
	if (conid != -1)
	{
		SendData(conid, toArray("!" + map));
	}
}