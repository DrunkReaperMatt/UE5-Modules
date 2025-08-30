// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"


UQuestStatus::UQuestStatus()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UQuestStatus::UpdateQuests(USM_InputAtom* QuestActivity)
{
	QuestActivities.Add(QuestActivity);

	for (int32 i = QuestList.Num() - 1; i >= 0; i--)
	{
		if (QuestList[i].UpdateQuest(this, QuestActivity))
		{
			UE_LOG(LogTemp, Warning, TEXT("Quest '%s' completed %s"), *QuestList[i].Quest->QuestName.ToString(),
				(QuestList[i].QuestProgress == EQuestCompletion::EQC_Succeeded) ? TEXT("Success") : TEXT("Failed"));
		}
	}
}
