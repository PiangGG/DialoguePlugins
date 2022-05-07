// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/DialogueTriggerConditionManager.h"

#include "Data/DialogueTriggerCondition.h"
#include "Manager/GlobalSaveManager.h"

int32 UDialogueTriggerConditionManager::DetectionLineNum( const UDataTable* InDT, const FString& InName)
{
	if (!InDT || InName == TEXT(""))
	{
		return 0;
	}

	TArray<FDialogueTriggerCondition*> FoundRows;
	InDT->GetAllRows<FDialogueTriggerCondition>(TEXT(""), FoundRows);

	if (const auto Num = FoundRows.Num())
	{
		for (int32 i = Num - 1; i >= 0; i--)
		{
			if (const auto& Row = FoundRows[i])
			{
				if (Row->NPCName == InName)
				{
					//获取保存的道具信息
					const auto& Props = UGlobalSaveManager::GetPropsName();

					//获取保存的任务信息
					FMissionStruct MissionInfo;
					int32 MainMissionIndex = 0;
					TArray<int32> SubMissionFlags;
					const bool bGetMission = UGlobalSaveManager::GetMissionInfo(MissionInfo, MainMissionIndex, SubMissionFlags);
					if (!bGetMission)
					{
						return 0;
					}

					//检查物品条件
					const bool bItemCondition = DetectionItem(Props, Row->PlayerOwnedItem);
					//检查任务条件
					const bool bMissionCondition = DetectionMission(MainMissionIndex, SubMissionFlags, Row->MainMissionCompletedInfo);

					if (bItemCondition && bMissionCondition)
					{
						return Row->JumpToLineNum;
					}
				}
			}
		}
	}

	return 0;
}

bool UDialogueTriggerConditionManager::DetectionItem(const TArray<FString>& InProps, const TArray<FString>& InCondition)
{
	if (InCondition.Num())
	{
		if (!InProps.Num())
		{
			return false;
		}

		for (const auto& Tmp : InCondition)
		{
			if (!InProps.Contains(Tmp))
			{
				return false;
			}
		}
	}

	return true;
}

bool UDialogueTriggerConditionManager::DetectionMission(int32 InMainIndex, const TArray<int32>& InFlags, const FMissionCompletedInfo& InCondition)
{
	if (InCondition.MainMissionIndex != INDEX_NONE)
	{
		if (InMainIndex < InCondition.MainMissionIndex)
		{
			return false;
		}

		if (InMainIndex == InCondition.MainMissionIndex)
		{
			if (InCondition.SubMissions.Num())
			{
				for (const auto& Tmp : InCondition.SubMissions)
				{
					if (!InFlags.IsValidIndex(Tmp))
					{
						return false;
					}

					if (!InFlags[Tmp])
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool UDialogueTriggerConditionManager::IndependentCheckItem(const TArray<FString>& InCondition)
{
	const auto& Props = UGlobalSaveManager::GetPropsName();
	return DetectionItem(Props, InCondition);
}

bool UDialogueTriggerConditionManager::IndependentCheckMission(const struct FMissionCompletedInfo& InCondition)
{
	FMissionStruct MissionInfo;
	int32 MainMissionIndex = 0;
	TArray<int32> SubMissionFlags;
	if (UGlobalSaveManager::GetMissionInfo(MissionInfo, MainMissionIndex, SubMissionFlags))
	{
		return DetectionMission(MainMissionIndex, SubMissionFlags, InCondition);
	}

	return false;
}