// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GlobalSaveManager.h"
#include "JsonObjectConverter.h"
#include "Interface/InteractionWidgetInterface.h"
#include "Blueprint/UserWidget.h"

//存档信息
FSaveStruct UGlobalSaveManager::SaveInfo;
//任务数据表
UDataTable* UGlobalSaveManager::MissionData = nullptr;
//是否完成初始化
bool UGlobalSaveManager::bInitialized = false;

//初始化存档
void UGlobalSaveManager::InitSaveInfo(UObject* WorldContextObject, UDataTable* InMissionData)
{
	if (!bInitialized)
	{
		MissionData = InMissionData;

		if (MissionData)
		{
			bInitialized = true;
		}

		LoadGameData(WorldContextObject);
	}
}

//玩家离开时重置存档
void UGlobalSaveManager::ResetSaveInfo()
{
	InitSaveStruct();
	bInitialized = false;
	MissionData = nullptr;
}

//添加道具
void UGlobalSaveManager::AddProp(const FString& InName)
{
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("GlobalSaveManager has not been initialized!"))
		return;
	}

	SaveInfo.Props.AddUnique(InName);
}

//保存玩家位置
void UGlobalSaveManager::SavePlayerTrans(const FTransform& InTrans)
{
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("GlobalSaveManager has not been initialized!"))
			return;
	}

	SaveInfo.SavedPlayerTrans = InTrans;
}

//完成主任务
void UGlobalSaveManager::CompletingMainMission(const int32 MainIndex, UUserWidget* InMainUI)
{
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("GlobalSaveManager has not been initialized!"))
		return;
	}

	if (MainIndex == SaveInfo.MainMissionIndex)
	{
		SaveInfo.MainMissionIndex += 1;
		InitSubMission();
	}

	IInteractionWidgetInterface* MainUI = Cast<IInteractionWidgetInterface>(InMainUI);
	if (MainUI)
	{
		MainUI->UpdateMission();
	}
}

//完成子任务
bool UGlobalSaveManager::CompletingSubMission(const int32 MainIndex, const int32 index, UUserWidget* InMainUI)
{
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("GlobalSaveManager has not been initialized!"))
		return false;
	}

	if (SaveInfo.SubMissionFlags.IsValidIndex(index) && MainIndex == SaveInfo.MainMissionIndex)
	{
		SaveInfo.SubMissionFlags[index] = 1;

		if (!CheckMainMissionCompleted(InMainUI))
		{
			IInteractionWidgetInterface* MainUI = Cast<IInteractionWidgetInterface>(InMainUI);
			if (MainUI)
			{
				MainUI->UpdateMission();
			}
		}

		return true;
	}

	return false;
}

//获取当前任务信息
bool UGlobalSaveManager::GetMissionInfo(FMissionStruct& MissionInfo, int32& CurrentMainMissionIndex, TArray<int32>& SubMissionFlags)
{
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("GlobalSaveManager has not been initialized!"))
		return false;
	}

	if (!MissionData)
	{
		UE_LOG(LogTemp, Warning, TEXT("MissionDataPtr is nullptr!"))
		return false;
	}

	auto FoundRow = MissionData->FindRow<FMissionStruct>(FName(FString::FromInt(SaveInfo.MainMissionIndex)), TEXT("Try Get MissionDataRow"));
	if (FoundRow)
	{
		MissionInfo = *FoundRow;
		CurrentMainMissionIndex = SaveInfo.MainMissionIndex;
		SubMissionFlags = SaveInfo.SubMissionFlags;
		return true;
	}

	return false;
}

//保存游戏进度
void UGlobalSaveManager::SaveGameData(UObject* WorldContextObject)
{
	/*FString SaveString;
	if (FJsonObjectConverter::UStructToJsonObjectString<FSaveStruct>(SaveInfo, SaveString, 0, 0, 0, nullptr, false))
	{
		UDTLinkFun::SaveInfo(WorldContextObject, TEXT("GameSave"), SaveString);
	}*/
}

//读取游戏进度
void UGlobalSaveManager::LoadGameData(UObject* WorldContextObject)
{
	/*FString LoadString = UDTLinkFun::LaodInfo(WorldContextObject, TEXT("GameSave"));
	if (LoadString != TEXT("") && FJsonObjectConverter::JsonObjectStringToUStruct<FSaveStruct>(LoadString, &SaveInfo))
	{
		FMissionStruct* Found = MissionData->FindRow<FMissionStruct>(FName(FString::FromInt(SaveInfo.MainMissionIndex)), TEXT(""));
		if (Found && Found->SubMissions.Num() == SaveInfo.SubMissionFlags.Num())
		{
			UE_LOG(LogTemp, Log, TEXT("Load SaveInfo Success!"))
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("MissionError"))
			InitSaveStruct();
		}
	}
	else
	{
		InitSaveStruct();
	}*/
}

//获取所有道具名称
const TArray<FString>& UGlobalSaveManager::GetPropsName()
{
	return SaveInfo.Props;
}

//检查是否完成当前所有子任务
bool UGlobalSaveManager::CheckMainMissionCompleted(UUserWidget* InMainUI)
{
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("GlobalSaveManager has not been initialized!"))
		return false;
	}

	for (const auto& Tmp : SaveInfo.SubMissionFlags)
	{
		if (Tmp == 0)
			return false;
	}

	CompletingMainMission(SaveInfo.MainMissionIndex, InMainUI);
	return true;
}

//初始化存档结构体
void UGlobalSaveManager::InitSaveStruct()
{
	SaveInfo.Props.Empty();
	SaveInfo.MainMissionIndex = 0;
	InitSubMission();
}

//初始化子任务
void UGlobalSaveManager::InitSubMission()
{
	SaveInfo.SubMissionFlags.Empty();
	if (MissionData)
	{
		auto FoundRow = MissionData->FindRow<FMissionStruct>(FName(FString::FromInt(SaveInfo.MainMissionIndex)), TEXT("Try Get MissionDataRow"));
		if (FoundRow)
		{
			SaveInfo.SubMissionFlags.Init(0, FoundRow->SubMissions.Num());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MissionDataPtr is nullptr!"))
	}
}