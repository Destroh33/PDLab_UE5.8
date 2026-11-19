// Fill out your copyright notice in the Description page of Project Settings.


#include "CrowdAIController.h"

ACrowdAIController::ACrowdAIController(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}

void ACrowdAIController::BeginPlay()
{
	Super::BeginPlay();

	UCrowdFollowingComponent* CrowdFollowingComponent = FindComponentByClass<UCrowdFollowingComponent>();

	if (CrowdFollowingComponent) {
		CrowdFollowingComponent->SetCrowdSeparation(true);
		CrowdFollowingComponent->SetCrowdSeparationWeight(crowdSeparationWeight);
		CrowdFollowingComponent->SetCrowdAvoidanceRangeMultiplier(crowdAvoidanceRangeMul);
		//CrowdFollowingComponent->SetCrowdAvoidanceQuality(crowdAvoidanceQType);
		CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
	}
}
