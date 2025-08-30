// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SM_State.generated.h"

class USM_Branch;
class USM_State;

UENUM()
enum class EStateMachineCompletionType
{
	NotAccepted,
	Accepted,
	Rejected,
	OutOfSteps UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct STATEMACHINE_API FStateMachineResult
{
	GENERATED_BODY()

	UPROPERTY()
	EStateMachineCompletionType CompletionType;

	UPROPERTY()
	USM_State* FinalState;

	UPROPERTY()
	int32 DataIndex;
};

UCLASS()
class STATEMACHINE_API USM_InputAtom : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName Description;
};

UCLASS(EditInlineNew)
class STATEMACHINE_API USM_Branch : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual  USM_State* TryBranch(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex, int32& OutDataIndex );

protected:
	UPROPERTY(EditAnywhere)
	USM_State* DestinationState;

	UPROPERTY(EditAnywhere)
	uint32 bReverseInputTest : 1;

	UPROPERTY(EditAnywhere)
	TArray<USM_InputAtom*> AcceptableInputs;
};

/**
 * 
 */
UCLASS()
class STATEMACHINE_API USM_State : public UDataAsset
{
	GENERATED_BODY()

public:

	USM_State();

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	virtual FStateMachineResult RunState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex = 0, int32 RemainingSteps = -1);

protected:
	virtual FStateMachineResult LoopState(const UObject* RefObject, const TArray<USM_InputAtom*>& DataSource, int32 DataIndex, int32 RemainingSteps);

	UPROPERTY(EditAnywhere)
	EStateMachineCompletionType CompletionType;

	UPROPERTY(EditAnywhere)
	uint32 bTerminateImmediately : 1;

	UPROPERTY(EditAnywhere)
	uint32 bLoopByDefault : 1;

	UPROPERTY(EditAnywhere, Instanced)
	TArray<USM_Branch*> InstancedBranches;
};
