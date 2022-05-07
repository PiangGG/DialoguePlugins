// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueInfo.generated.h"

UENUM(BlueprintType)
enum class EDialogueState : uint8
{
    NONE        UMETA(DisplayName = "空闲"),
    TALK        UMETA(DisplayName = "闲聊"),
    DIALOGUE    UMETA(DisplayName = "对话")
};

UENUM(BlueprintType)
enum class EDialogueAction : uint8
{
    NEXT            UMETA(DisplayName = "下一句"),
    ANSWER          UMETA(DisplayName = "回答"),
    TRIGGEREVENT    UMETA(DisplayName = "触发事件"),
    QUIT            UMETA(DisplayName = "退出对话")
};

USTRUCT(BlueprintType)
struct FAnswerContent : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "回答内容"), Category = "回答结构")
    FString AnswerContent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "跳转行名"), Category = "回答结构")
    int32 JumpLineNum;
};

USTRUCT(BlueprintType)
struct FDialogueContent : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "对话名称"), Category = "对话结构")
    FString DialogueName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "对话内容"), Category = "对话结构")
    FString DialogueContent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "对话结束后的操作"), Category = "对话结构")
    EDialogueAction CompletedAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "触发事件名"), Category = "对话结构")
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "回答内容"), Category = "对话结构")
    TArray<FAnswerContent> AnswerContent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "保存下一行"), Category = "对话结构")
    int32 SaveNextLine;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "对话音频"))
    USoundBase* Sound;
};

USTRUCT(BlueprintType)
struct FTalkContent : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "NPC名称"))
	FString NPCName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "闲聊内容"))
	TArray<FString> TalkContent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "闲聊音频"))
    TArray<USoundBase*> Sound;
};