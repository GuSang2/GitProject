// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_FindRandomLocation::UBTTaskNode_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");
	bCreateNodeInstance = true; // 인스턴스마다 다르게 설정 가능하게
}

EBTNodeResult::Type UBTTaskNode_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = ControlledPawn->GetActorLocation();
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(ControlledPawn->GetWorld());

	if (NavSystem)
	{
		FNavLocation RandomPoint;
		if (NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, RandomPoint))
		{
			// Blackboard에 저장
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomPoint.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
