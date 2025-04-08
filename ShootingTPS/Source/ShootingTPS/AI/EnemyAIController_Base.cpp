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
	UE_LOG(LogTemp, Warning, TEXT("OnPossess: Entered function"));

	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess: Called Super::OnPossess"));

	if (BehaviorTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnPossess: BehaviorTree is valid"));

		RunBehaviorTree(BehaviorTree);
		UE_LOG(LogTemp, Warning, TEXT("OnPossess: RunBehaviorTree executed"));

		UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
		UE_LOG(LogTemp, Warning, TEXT("OnPossess: BlackboardComp = %s"), BlackboardComp ? TEXT("Valid") : TEXT("NULL"));

		if (BlackboardComp)
		{
			UWorld* World = GetWorld();
			UE_LOG(LogTemp, Warning, TEXT("OnPossess: World = %s"), World ? TEXT("Valid") : TEXT("NULL"));

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
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnPossess: BehaviorTree is NULL"));
	}
}

