// Fill out your copyright notice in the Description page of Project Settings.


#include "TextReader.h"

// Sets default values for this component's properties
UTextReader::UTextReader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTextReader::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTextReader::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTextReader::InitReader(FString CsvFileName) {

	FString csvfullname = FPaths::ProjectDir() + CsvFileName;
	UE_LOG(LogTemp, Warning, TEXT("Reading csv file at: %s"), *csvfullname);

	if (FPaths::FileExists(csvfullname)) {
		if (!fileopened) {
			csvfile.open(std::string(TCHAR_TO_UTF8(*csvfullname)));
			fileopened = true;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find csvFileName: %s"), *csvfullname);
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Could not find csvfile: " + csvfullname));
	}
}

bool UTextReader::ReadCSVline(FString& LineRead) {
	if (fileopened) {
		linecounter++;
		if (std::getline(csvfile, csvline)) {
			LineRead = csvline.c_str();
			return true;
		}
		else {
			LineRead = "file ended.";
			csvfile.close();
			fileopened = false;
			return false;
		}
	}
	else {
		LineRead = "file ended.";
		return false;
	}
}