// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "CrowdAIController.generated.h"

/**
 * 
 */
UCLASS()
class SUTHANALAB_API ACrowdAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "CrowdAI", BlueprintReadWrite) float crowdSeparationWeight = 50.0f;
	UPROPERTY(EditAnywhere, Category = "CrowdAI", BlueprintReadWrite) float crowdAvoidanceRangeMul = 1.1f;
	//UPROPERTY(EditAnywhere, Category = "CrowdAI", BlueprintReadWrite) ECrowdAvoidanceQuality::Type crowdAvoidanceQType = ECrowdAvoidanceQuality::Low;

	ACrowdAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void BeginPlay() override;	
};
