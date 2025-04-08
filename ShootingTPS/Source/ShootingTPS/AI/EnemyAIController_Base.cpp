// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Base.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController_Base::StopBehaviorTree()
{
	if (BrainComponent)
	{
		BrainComponent->StopLogic(TEXT("BT Stop"));
	}
}

void AEnemyAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);

		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		if (BlackboardComp)
		{
			UWorld* World = GetWorld();
			APlayerController* PlayerController = World->GetFirstPlayerController();
			APawn* PlayerPawn = PlayerController->GetPawn();
			BlackboardComp->SetValueAsObject("TargetPlayer", PlayerPawn);
		}
	}
}
