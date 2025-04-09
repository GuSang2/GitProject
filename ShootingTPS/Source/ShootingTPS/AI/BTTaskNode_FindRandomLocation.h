// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGTPS_API UBTTaskNode_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FindRandomLocation();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	// 블랙보드 키 설정용
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetLocationKey;

	// 탐색 반경
	UPROPERTY(EditAnywhere, Category = "Search")
	float SearchRadius = 1000.f;
};
