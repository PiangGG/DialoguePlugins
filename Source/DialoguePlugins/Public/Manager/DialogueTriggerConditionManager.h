// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueTriggerConditionManager.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEPLUGINS_API UDialogueTriggerConditionManager : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta =(DisplayName = "检查NPC对话行数"))
	static int32 DetectionLineNum(const class UDataTable* InDT, const FString& InName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "判断物品条件"))
	static bool DetectionItem(const TArray<FString>& InProps, const TArray<FString>& InCondition);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "判断任务条件"))
	static bool DetectionMission(int32 InMainIndex, const TArray<int32>& InFlags, const struct FMissionCompletedInfo& InCondition);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "独立判断物品条件"))
	static bool IndependentCheckItem(const TArray<FString>& InCondition);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "独立判断任务条件"))
	static bool IndependentCheckMission(const struct FMissionCompletedInfo& InCondition);
};
