// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UAIPerceptionComponent* AIPerception = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UAISenseConfig_Sight* SightConfig = nullptr;
};
