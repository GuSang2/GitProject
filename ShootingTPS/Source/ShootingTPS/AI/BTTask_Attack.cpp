// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

//EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	AAIController* AIController = OwnerComp.GetAIOwner();
//	if (AIController)
//	{
//		APawn* ControlledPawn = AIController->GetPawn();
//		if (ControlledPawn)
//		{
//			ControlledPawn->Attack();
//			return EBTNodeResult::Succeeded;
//		}
//	}
//	return EBTNodeResult::Failed();
//}
