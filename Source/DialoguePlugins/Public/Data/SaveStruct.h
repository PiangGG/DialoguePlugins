#pragma once

#pragma once

#include "CoreMinimal.h"
#include "SaveStruct.generated.h"

USTRUCT()
struct FSaveStruct
{
	GENERATED_USTRUCT_BODY()

	//道具
	UPROPERTY()
	TArray<FString> Props;

	//主任务序号
	UPROPERTY()
	int32 MainMissionIndex;

	//子任务完成标记
	UPROPERTY()
	TArray<int32> SubMissionFlags;

	//保存的玩家位置
	UPROPERTY()
	FTransform SavedPlayerTrans;
};
