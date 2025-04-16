// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController_Base.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGTPS_API AEnemyAIController_Base : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController_Base();

	void StopBehaviorTree();

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;
};
