// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/DialogueInfo.h"
#include "DialogueWidgets/DialogueWidget.h"
#include "DialogueComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTalkEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuitDialogueDelegate);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "触发闲聊"))
	void TriggerTalk();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "结束闲聊"))
	void OnTalkEnd();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "触发对话"))
	void TriggerDialogue();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "对话结束之后的操作"))
	void CheckAction();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "结束对话"))
	void QuitDialogue();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "跳转到指定行"))
	void JumpTo(int32 InNum);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "独立触发对话"))
	void IndependentDialogue(UDataTable* InScript);

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected, DisplayName = "更新闲聊UI内容"))
	void UpdateTalkContent(const FString& Name, const FString& Content);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected, DisplayName = "创建对话UI"))
	void CreateDialogueUI(const FDialogueContent& DialogueInfo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected, DisplayName = "创建回答UI"))
	void CreateAnswer();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (BlueprintProtected, DisplayName = "删除对话UI"))
	void DeleteDialogueUI();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintProtected, DisplayName = "获取对话内容"))
	bool GetDialogueInfo(FDialogueContent& DialogueInfo);

private:

	void PlayTalkSound(const TArray<USoundBase*>& InSounds);

	void PlayDialogueSound(USoundBase* InSound);

	void DeleteSoundAndTimer();

private:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "闲聊剧本"))
	UDataTable* TalkDT;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "对话剧本"))
	UDataTable* DialogueDT;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "对话条件表"))
	UDataTable* DialogueConditionDT;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "对话对象名称"))
	FString DialogueName;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "对话UI蓝图类"))
	TSubclassOf<UDialogueWidget> DialogueWidgetBPClass;

	UPROPERTY()
	UAudioComponent* DialogueSoundComp;

	UPROPERTY()
	UDialogueWidget* DialogueWidget;

	int32 DialogueNum;

	int32 TalkNum;

	FTimerHandle NoneSoundTimer;

public:

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "结束闲聊时"))
	FTalkEndDelegate OnTalkEndDelegate;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "结束对话时"))
	FQuitDialogueDelegate OnQuitDialogueDelegate;	
};
