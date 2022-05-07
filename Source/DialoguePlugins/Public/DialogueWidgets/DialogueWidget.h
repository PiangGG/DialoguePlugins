// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/DialogueInfo.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class USizeBox;
class UVerticalBox;
class UDialogueComponent;
class UAnswerWidget;
UCLASS()
class DIALOGUEPLUGINS_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "更新对话"))
	void UpdateDialogue(const FDialogueContent& InContent);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "创建回答窗口"))
	void CreateAnswerButtons(const FDialogueContent& InContent);

	const TArray<UWidget*> GetAnswerButtons();

	void InitDialogue(UDialogueComponent* InComp);

protected:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "点击跳过", BlueprintProtected))
	void TouchJump();

private:

	void DeleteAnswerButtons();

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextContent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NPCName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* AnswerSizeBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* AnswerBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", BlueprintProtected))
	UDialogueComponent* DialogueComponent;

private:

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "回答按钮控件"))
	TSubclassOf<UAnswerWidget> BP_AnswerButtonWidget;
};
