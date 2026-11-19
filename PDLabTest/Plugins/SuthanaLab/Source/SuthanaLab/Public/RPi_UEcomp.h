// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Networking.h"


#include "RPi_UEcomp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUTHANALAB_API URPi_UEcomp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPi_UEcomp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	FSocket* Socket;

	// Local Endpoint
	FString SocketDescription = "UDP Listen Socket";
	FIPv4Endpoint LocalEndpoint;
	UPROPERTY(EditAnywhere, Category = "RPi", BlueprintReadWrite) int LocalPort = 54000;
	int32 SendSize;
	TArray<uint8> ReceivedData;

	// Remote Endpoint
	FIPv4Endpoint RemoteEndpoint;
	FIPv4Address RemoteAddress;
	UPROPERTY(EditAnywhere, Category = "RPi", BlueprintReadWrite) int RemotePort = 54001;
	int32 BufferSize;
	UPROPERTY(EditAnywhere, Category = "RPi", BlueprintReadWrite) FString IP = "192.168.50.232";
	//FString IP = "127.0.0.1";

	ISocketSubsystem* SocketSubsystem;

	UPROPERTY(EditAnywhere, Category = "RPi", BlueprintReadWrite)	bool commEstablished;
	UPROPERTY(EditAnywhere, Category = "RPi", BlueprintReadWrite)	bool doListen;


	UFUNCTION(BlueprintCallable, Category = "RPi", meta = (Keywords = "Close Comms"))
	void CloseComms();
	UFUNCTION(BlueprintCallable, Category = "RPi", meta = (Keywords = "Init Comm"))
	void InitComm();
		
	void Listen();

	UFUNCTION(BlueprintCallable, Category = "RPi")
	bool sendMessage(FString Message);
	
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
