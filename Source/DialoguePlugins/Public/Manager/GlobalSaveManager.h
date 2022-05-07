// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "Data/SaveStruct.h"
#include "Data/MissionStruct.h"
#include "GlobalSaveManager.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEPLUGINS_API UGlobalSaveManager : public UObject
{
	GENERATED_BODY()

private:
	//存档信息
	static FSaveStruct SaveInfo;
	//任务数据表
	static UDataTable* MissionData;
	//是否完成初始化
	static bool bInitialized;
	
public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DisplayName = "初始化存档"))
	static void InitSaveInfo(UObject* WorldContextObject, UDataTable* InMissionData);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "玩家离开时重置存档"))
	static void ResetSaveInfo();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "添加道具"))
	static void AddProp(const FString& InName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "保存玩家位置"))
	static void SavePlayerTrans(const FTransform& InTrans);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "完成主任务"))
	static void CompletingMainMission(const int32 MainIndex, class UUserWidget* InMainUI);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "完成子任务"))
	static bool CompletingSubMission(const int32 MainIndex, const int32 index, class UUserWidget* InMainUI);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "获取当前任务信息"))
	static bool GetMissionInfo(FMissionStruct& MissionInfo, int32& CurrentMainMissionIndex, TArray<int32>& SubMissionFlags);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DisplayName = "保存游戏进度"))
	static void SaveGameData(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DisplayName = "读取游戏进度"))
	static void LoadGameData(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "获取所有道具名称"))
	static const TArray<FString>& GetPropsName();

private:
	//检查是否完成当前所有子任务
	static bool CheckMainMissionCompleted(UUserWidget* InMainUI);
	//初始化存档结构体
	static void InitSaveStruct();
	//初始化子任务
	static void InitSubMission();
};
