// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnswerWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUEPLUGINS_API UAnswerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitAnswer(const FText& InContent, int32 InJumpNum, class UDialogueComponent* InComp, class UDialogueWidget* InWidget);

protected:

	virtual void NativeDestruct() override;

protected:

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void JumpToLine();

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void PlayAnim();

public:

	UFUNCTION(BlueprintImplementableEvent)
	void PlayBPAnim();

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AnswerContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", BlueprintProtected))
	FText TextContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", BlueprintProtected))
	int32 JumpLineNum;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true", BlueprintProtected))
	class UDialogueComponent* DialogueComponent;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true", BlueprintProtected))
	class UDialogueWidget* DialogueWidget;
};
