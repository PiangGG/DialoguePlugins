#pragma once


#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EInteractiveType : uint8
{
	PROP        UMETA(DisplayName = "道具"),
	NPC         UMETA(DisplayName = "NPC"),
	PLAYER      UMETA(DisplayName = "玩家"),
	NONE        UMETA(DisplayName = "不可交互")
};