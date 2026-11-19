// Fill out your copyright notice in the Description page of Project Settings.


#include "RPi_UEcomp.h"

// Sets default values for this component's properties
URPi_UEcomp::URPi_UEcomp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Socket = nullptr;
}


// Called when the game starts
void URPi_UEcomp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SocketSubsystem = nullptr;
}


// Called every frame
void URPi_UEcomp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (doListen) {
		Listen(); // Listen for messages
	}

	//FString t = "test222";
	//sendMessage(t); // Send Message Test
}

void URPi_UEcomp::BeginDestroy() {
	Super::BeginDestroy();

	this->CloseComms();
}
void URPi_UEcomp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	this->CloseComms();
}

void URPi_UEcomp::InitComm() {
	if (!commEstablished) {
		if (SocketSubsystem == nullptr)	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

		SendSize = 2 * 1024 * 1024;
		BufferSize = 2 * 1024 * 1024;

		LocalEndpoint = FIPv4Endpoint(FIPv4Address::Any, LocalPort);

		FIPv4Address::Parse(IP, RemoteAddress);
		RemoteEndpoint = FIPv4Endpoint(RemoteAddress, RemotePort);

		Socket = nullptr;

		if (SocketSubsystem != nullptr)
		{
			if (Socket == nullptr)
			{
				Socket = FUdpSocketBuilder(SocketDescription)
					.AsNonBlocking()
					.AsReusable()
					.BoundToEndpoint(LocalEndpoint)
					.WithReceiveBufferSize(SendSize)
					.WithReceiveBufferSize(BufferSize)
					.WithBroadcast();
			}
		}

		//open comms
		commEstablished = true;
	}
}

void URPi_UEcomp::CloseComms() {
	if (commEstablished) {
		SocketSubsystem->DestroySocket(Socket);
		Socket = nullptr;
		SocketSubsystem = nullptr;

		//close the comm
		commEstablished = false;
	}
}

void URPi_UEcomp::Listen()
{
	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	uint32 Size;
	while (Socket->HasPendingData(Size))
	{
		uint8* Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		Socket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);

		char ansiiData[1024];
		memcpy(ansiiData, ReceivedData.GetData(), BytesRead);
		ansiiData[BytesRead] = 0;

		FString data = ANSI_TO_TCHAR(ansiiData);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Message by UDP: " + data);
		UE_LOG(LogTemp, Warning, TEXT("Message by UDP : %s"), *data);
	}
}

bool URPi_UEcomp::sendMessage(FString Message)
{
	if (!Socket) return false;
	int32 BytesSent;

	FTimespan waitTime = FTimespan(10);

	TCHAR* serializedChar = Message.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);

	bool success = Socket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *RemoteEndpoint.ToInternetAddr());
	UE_LOG(LogTemp, Warning, TEXT("Sent message: %s : %s : Address - %s : BytesSent - %d"), *Message, (success ? TEXT("true") : TEXT("false")), *RemoteEndpoint.ToString(), BytesSent);

	if (success && BytesSent > 0) return true;
	else return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
