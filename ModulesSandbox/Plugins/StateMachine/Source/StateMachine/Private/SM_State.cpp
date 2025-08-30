// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/Classes/SM_State.h"

USM_State* USM_Branch::TryBranch(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex,
	int32& OutDataIndex)
{
	OutDataIndex = DataIndex;
	if (!AcceptableInputs.Num() || (DataSource.IsValidIndex(DataIndex) && AcceptableInputs.Contains(DataSource[DataIndex])))
	{
		++OutDataIndex;
		return bReverseInputTest ? nullptr : DestinationState;
	}
	
	return bReverseInputTest ? DestinationState : nullptr;
}

USM_State::USM_State()
{
	bLoopByDefault = true;
}

FStateMachineResult USM_State::RunState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource,
	int32 DataIndex, int32 RemainingSteps)
{
	bool bMustEndNow = (bTerminateImmediately || !DataSource.IsValidIndex(DataIndex));
	
	if (RemainingSteps && !bMustEndNow)
	{
		USM_State* DestinationState = nullptr;
		int32 DestinationDataIndex = DataIndex;

		// TODO
		for (int32 i = 0; i < InstancedBranches.Num(); ++i)
		{
			if (!InstancedBranches[i])
			{
				continue;
			}

			DestinationState = InstancedBranches[i]->TryBranch(RefObject, DataSource, DataIndex, DestinationDataIndex);
			if (DestinationState)
			{
				return DestinationState->RunState(RefObject, DataSource, DestinationDataIndex, RemainingSteps - 1);
			}
		}

		if (bLoopByDefault)
		{
			return LoopState(RefObject, DataSource, DataIndex, RemainingSteps);
		}

		bMustEndNow = true;
	}
	FStateMachineResult SMR;
	SMR.FinalState = this;
	SMR.DataIndex = DataIndex;
	SMR.CompletionType = bMustEndNow ? CompletionType : EStateMachineCompletionType::OutOfSteps;
	return SMR;
}

FStateMachineResult USM_State::LoopState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource,
	int32 DataIndex, int32 RemainingSteps)
{

	return FStateMachineResult();
}
