// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidgets/AnswerWidget.h"
#include "Component/DialogueComponent.h"
#include "Components/TextBlock.h"
#include "DialogueWidgets/DialogueWidget.h"

void UAnswerWidget::InitAnswer(const FText& InContent, int32 InJumpNum, class UDialogueComponent* InComp, class UDialogueWidget* InWidget)
{
	TextContent = InContent;
	JumpLineNum = InJumpNum;
	DialogueComponent = InComp;
	DialogueWidget = InWidget;

	AnswerContent->SetText(TextContent);
}

void UAnswerWidget::NativeDestruct()
{
	Super::NativeDestruct();
	TextContent = FText::FromString(TEXT(""));
	JumpLineNum = 0;
	DialogueComponent = nullptr;
}

void UAnswerWidget::JumpToLine()
{
	if (DialogueComponent)
	{
		DialogueComponent->JumpTo(JumpLineNum);
	}
}

void UAnswerWidget::PlayAnim()
{
	if (DialogueWidget)
	{
		auto Buttons = DialogueWidget->GetAnswerButtons();
		for (const auto& Tmp : Buttons)
		{
			if (Tmp && Tmp != this)
			{
				if (auto Other = Cast<UAnswerWidget>(Tmp))
				{
					Other->PlayBPAnim();
				}
			}
		}
	}
}