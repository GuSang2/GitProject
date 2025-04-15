// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Base.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController_Base::AEnemyAIController_Base()
{
	// Perception 컴포넌트 초기화
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = 1200.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerception->ConfigureSense(*SightConfig);
		AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
	}
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

	// 이벤트 바인딩
	if (AIPerception)
	{
		AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController_Base::OnTargetPerceptionUpdated);
	}
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
	UE_LOG(LogTemp, Warning, TEXT("Perception Updated: %s, Success: %d"), *Actor->GetName(), Stimulus.WasSuccessfullySensed());

	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		// 감지 성공 (시야에 들어왔을 때)
		BB->SetValueAsObject("TargetPlayer", Actor);
		UE_LOG(LogTemp, Warning, TEXT("Set TargetPlayer to %s"), *Actor->GetName());
	}
	else
	{
		// 감지 실패 (시야에서 사라짐)
		BB->ClearValue("TargetPlayer");
		UE_LOG(LogTemp, Warning, TEXT("Clear TargetPlayer"));
	}
}

