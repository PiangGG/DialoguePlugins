#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueTriggerCondition.generated.h"

USTRUCT(BlueprintType)
struct FMissionCompletedInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMissionCompletedInfo()
		: MainMissionIndex(INDEX_NONE)
	{}

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "主任务ID"))
	int32 MainMissionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "子任务完成情况"))
	TArray<int32> SubMissions;
};

USTRUCT(BlueprintType)
struct FDialogueTriggerCondition : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "NPC名字或编号"))
	FString NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "主角拥有的物品"))
	TArray<FString> PlayerOwnedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "主线任务完成情况"))
	FMissionCompletedInfo MainMissionCompletedInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "跳转到某一行（数字）"))
	int32 JumpToLineNum;
};
