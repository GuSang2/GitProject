// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Base.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController_Base::AEnemyAIController_Base()
{

}

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
			APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;
			UE_LOG(LogTemp, Warning, TEXT("OnPossess: PlayerController = %s"), PlayerController ? TEXT("Valid") : TEXT("NULL"));

			APawn* PlayerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;
			UE_LOG(LogTemp, Warning, TEXT("OnPossess: PlayerPawn = %s"), PlayerPawn ? TEXT("Valid") : TEXT("NULL"));

			if (PlayerPawn)
			{
				BlackboardComp->SetValueAsObject("TargetPlayer", PlayerPawn);
				UE_LOG(LogTemp, Warning, TEXT("OnPossess: Set TargetPlayer on Blackboard"));
			}
		}
	}
}

void AEnemyAIController_Base::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

}

