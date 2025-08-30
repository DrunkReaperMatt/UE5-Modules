// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataAsset.h"
#include "SM_State.h"
#include "Quest.generated.h"

class USM_InputAtom;
class USM_State;

UENUM()
enum class EQuestCompletion : uint8
{
	EQC_NotStarted,
	EQC_Started,
	EQC_Succeeded,
	EQC_Failed
};

/**
 * 
 */
UCLASS()
class STATEMACHINEDEMO_API UQuest : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FText QuestName;

	UPROPERTY(EditAnywhere)
	USM_State* QuestStateMachine;

	UPROPERTY(EditAnywhere)
	uint32 bInputBlackList : 1;

	UPROPERTY(EditAnywhere)
	TArray<USM_InputAtom*> InputLists;
};

USTRUCT()
struct FQuestInProgress
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	const UQuest* Quest;

	UPROPERTY(EditAnywhere)
	EQuestCompletion QuestProgress;

protected:
	UPROPERTY(EditAnywhere)
	TArray<USM_InputAtom*> QuestActivities;
	
public:
	bool UpdateQuest(const UObject* ObjectRef, USM_InputAtom* QuestActivity)
	{
		if (Quest && (QuestProgress == EQuestCompletion::EQC_Started) && (Quest->bInputBlackList != Quest->InputLists.Contains(QuestActivity)))
		{
			FStateMachineResult QuestResult;
			QuestActivities.Add(QuestActivity);
			QuestResult = Quest->QuestStateMachine->RunState(ObjectRef, QuestActivities);

			switch (QuestResult.CompletionType)
			{
			case EStateMachineCompletionType::Accepted:
				QuestProgress = EQuestCompletion::EQC_Succeeded;
				return true;
			case EStateMachineCompletionType::Rejected:
				QuestProgress = EQuestCompletion::EQC_Failed;
				return true;
			}
		}
		return false;
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STATEMACHINEDEMO_API UQuestStatus : public UActorComponent{
	GENERATED_BODY()

public:
	UQuestStatus();

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void UpdateQuests(USM_InputAtom* QuestActivity);

protected:

	UPROPERTY(EditAnywhere)
	TArray<USM_InputAtom*> QuestActivities;

	UPROPERTY(EditAnywhere)
	TArray<FQuestInProgress> QuestList;
};
