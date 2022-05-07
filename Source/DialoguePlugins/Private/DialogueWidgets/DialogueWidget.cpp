// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidgets/DialogueWidget.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "DialogueWidgets/AnswerWidget.h"
#include "Component/DialogueComponent.h"

void UDialogueWidget::UpdateDialogue(const FDialogueContent& InContent)
{
	DeleteAnswerButtons();
	TextContent->SetText(FText::FromString(InContent.DialogueContent));
	NPCName->SetText(FText::FromString(InContent.DialogueName));
}

void UDialogueWidget::CreateAnswerButtons(const FDialogueContent& InContent)
{
	if (InContent.AnswerContent.Num() && BP_AnswerButtonWidget && !AnswerBox->HasAnyChildren())
	{
		for (const auto& Tmp : InContent.AnswerContent)
		{
			if (auto Answer = CreateWidget<UAnswerWidget>(this, BP_AnswerButtonWidget))
			{
				Answer->InitAnswer(FText::FromString(Tmp.AnswerContent), Tmp.JumpLineNum, DialogueComponent, this);
				AnswerBox->AddChild(Answer);
				AnswerSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
		}
	}
}

const TArray<UWidget*> UDialogueWidget::GetAnswerButtons()
{
	return AnswerBox->GetAllChildren();
}

void UDialogueWidget::InitDialogue(UDialogueComponent* InComp)
{
	DialogueComponent = InComp;
}

void UDialogueWidget::TouchJump()
{
	if (DialogueComponent)
	{
		DialogueComponent->CheckAction();
	}
}

void UDialogueWidget::DeleteAnswerButtons()
{
	AnswerSizeBox->SetVisibility(ESlateVisibility::Hidden);
	AnswerBox->ClearChildren();
}