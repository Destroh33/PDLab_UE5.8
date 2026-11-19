// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//custom includes section
#include <fstream>
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
//end of custom includes section

#include "Logger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUTHANALAB_API ULogger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UWorld* uworldref;
	std::ofstream myfile;
	bool logopen;
	
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	float logRate = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	float logTimer;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FName LogName = "LogTest";
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector headpos;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector headrot;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector gazeOrigin;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector gazeDirection;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector fixationPoint;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector interceptPoint;

	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	float interceptDist;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FString interceptName;

	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector leftEyeOrigin;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector leftEyeDirection;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector rightEyeOrigin;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector rightEyeDirection;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector optipos;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector optirot;

	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FName customPosName = "CustomName";
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	FVector customPos;

	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	bool leftEyeBlink;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	bool rightEyeBlink;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	float leftPupil;
	UPROPERTY(EditAnywhere, Category = "Logger", BlueprintReadWrite)	float rightPupil;


	UFUNCTION(BlueprintCallable, Category = "Logger", meta = (Keywords = "Init Logger"))
	void InitializeLogger();
	UFUNCTION(BlueprintCallable, Category = "Logger", meta = (Keywords = "Close/Finish Logger"))
	void FinishLogger();
	UFUNCTION(BlueprintCallable, Category = "Logger", meta = (Keywords = "Log Line"))
	void LogLine(FString LogLine, FString logtype = "Event");
		
};
