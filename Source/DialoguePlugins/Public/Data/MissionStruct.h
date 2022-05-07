#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MissionStruct.generated.h"

USTRUCT(BlueprintType)
struct FSubMissionStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "子任务内容"))
	FString SubMissionContent;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "任务完成后的文字"))
	FString SuccessText;
};

USTRUCT(BlueprintType)
struct FMissionStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

 public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "主任务内容"))
	FString MainMissionContent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "子任务"))
	TArray<FSubMissionStruct> SubMissions;
};
