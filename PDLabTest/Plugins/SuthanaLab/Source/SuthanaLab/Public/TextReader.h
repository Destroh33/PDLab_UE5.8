// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <fstream>
#include <string>
#include "TextReader.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUTHANALAB_API UTextReader : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTextReader();
	bool fileopened;
	std::ifstream csvfile;
	std::string csvline;
	UPROPERTY(EditAnywhere, Category = "CSVreader", BlueprintReadWrite) int linecounter;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CSVreader", meta = (Keywords = "Init csvReader"))
	void InitReader(FString CsvFileName);
	UFUNCTION(BlueprintCallable, Category = "CSVreader", meta = (Keywords = "Read csvline"))
	bool ReadCSVline(FString& LineRead);
};
