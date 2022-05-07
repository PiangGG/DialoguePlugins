// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DialogueInfo.h"
#include "UObject/Object.h"
#include "GlobalDialogueManager.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEPLUGINS_API UGlobalDialogueManager : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "获取对话状态"))
	static const EDialogueState& GetDialogueState();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "设置对话状态"))
	static void SetDialogueState(EDialogueState InState);

private:

	static EDialogueState DialogueState;
};
