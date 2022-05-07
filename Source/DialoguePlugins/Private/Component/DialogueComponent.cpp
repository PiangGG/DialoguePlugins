// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DialogueComponent.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/DialogueTriggerConditionManager.h"
#include "Manager/GlobalDialogueManager.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
: DialogueSoundComp(nullptr)
, DialogueNum(0)
, TalkNum(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogueComponent::TriggerTalk()
{
	if (TalkDT && UGlobalDialogueManager::GetDialogueState() == EDialogueState::NONE)
	{
		if (auto Found = TalkDT->FindRow<FTalkContent>(*DialogueName, TEXT("")))
		{
			UGlobalDialogueManager::SetDialogueState(EDialogueState::TALK);

			if (Found->TalkContent.IsValidIndex(TalkNum))
			{
				UpdateTalkContent(Found->NPCName, Found->TalkContent[TalkNum]);
			}
				
			PlayTalkSound(Found->Sound);

			if (TalkNum >= (Found->TalkContent.Num() - 1))
			{
				TalkNum = 0;
			}
			else
			{
				TalkNum++;
			}
		}
	}
}

void UDialogueComponent::OnTalkEnd()
{
	UpdateTalkContent(TEXT(""), TEXT(""));
	
	DeleteSoundAndTimer();

	UGlobalDialogueManager::SetDialogueState(EDialogueState::NONE);
	if (OnTalkEndDelegate.IsBound())
	{
		OnTalkEndDelegate.Broadcast();
	}
}

void UDialogueComponent::TriggerDialogue()
{
	if (!DialogueWidget)
	{
		DialogueNum = UDialogueTriggerConditionManager::DetectionLineNum(DialogueConditionDT, DialogueName);
	}

	FDialogueContent Content;
	if (GetDialogueInfo(Content) && (UGlobalDialogueManager::GetDialogueState() != EDialogueState::DIALOGUE || DialogueWidget))
	{
		OnTalkEnd();
		UGlobalDialogueManager::SetDialogueState(EDialogueState::DIALOGUE);
		if (Content.DialogueContent != TEXT(""))
		{
			CreateDialogueUI(Content);
			PlayDialogueSound(Content.Sound);
		}
		else
		{
			CheckAction();
		}
	}
}

void UDialogueComponent::CheckAction()
{
	DeleteSoundAndTimer();

	FDialogueContent Content;
	if (GetDialogueInfo(Content))
	{
		switch (Content.CompletedAction)
		{
			case EDialogueAction::NEXT:
			{
				DialogueNum++;
				TriggerDialogue();
			}
			break;

			case EDialogueAction::ANSWER:
			{
				CreateAnswer();
			}
			break;

			case EDialogueAction::TRIGGEREVENT:
			{
				QuitDialogue();

				auto FoundFunc = GetOwner()->FindFunction(*Content.EventName);
				if (FoundFunc && (FoundFunc->ParmsSize == 0))
				{
					GetOwner()->ProcessEvent(FoundFunc, nullptr);
				}
				
			}
			break;
			
			case EDialogueAction::QUIT:
			{
				QuitDialogue();
			}
			break;
		}
	}
}

void UDialogueComponent::QuitDialogue()
{
	DeleteDialogueUI();

	/*FDialogueContent Content;
	if (GetDialogueInfo(Content))
	{
		DialogueNum = Content.SaveNextLine;
	}*/

	DialogueNum = 0;

	UGlobalDialogueManager::SetDialogueState(EDialogueState::NONE);
	if (OnQuitDialogueDelegate.IsBound())
	{
		OnQuitDialogueDelegate.Broadcast();
	}
}

void UDialogueComponent::JumpTo(int32 InNum)
{
	DialogueNum = InNum;
	TriggerDialogue();
}

void UDialogueComponent::IndependentDialogue(UDataTable* InScript)
{
	DialogueDT = InScript;
	TriggerDialogue();
}

void UDialogueComponent::UpdateTalkContent_Implementation(const FString& Name, const FString& Content)
{
}

void UDialogueComponent::CreateDialogueUI_Implementation(const FDialogueContent& DialogueInfo)
{
	if (DialogueWidget)
	{
		DialogueWidget->UpdateDialogue(DialogueInfo);
	}
	else if (DialogueWidgetBPClass)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetBPClass);

		if (DialogueWidget)
		{
			DialogueWidget->InitDialogue(this);
			DialogueWidget->AddToViewport();
			DialogueWidget->UpdateDialogue(DialogueInfo);
		}
	}
	else
	{
		QuitDialogue();
	}
}

void UDialogueComponent::CreateAnswer_Implementation()
{
	if (DialogueWidget)
	{
		FDialogueContent Content;
		if (GetDialogueInfo(Content))
		{
			DialogueWidget->CreateAnswerButtons(Content);
		}
		else
		{
			QuitDialogue();
		}
	}
	else
	{
		QuitDialogue();
	}
}

void UDialogueComponent::DeleteDialogueUI_Implementation()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
}

bool UDialogueComponent::GetDialogueInfo(FDialogueContent& DialogueInfo)
{
	if (!DialogueDT)
	{
		return false;
	}

	if (auto Found = DialogueDT->FindRow<FDialogueContent>(*FString::FromInt(DialogueNum), TEXT("")))
	{
		DialogueInfo = *Found;
		return true;
	}

	return false;
}

void UDialogueComponent::PlayTalkSound(const TArray<USoundBase*>& InSounds)
{
	DeleteSoundAndTimer();

	if (InSounds.IsValidIndex(TalkNum) && InSounds[TalkNum] && !DialogueSoundComp)
	{
		DialogueSoundComp = UGameplayStatics::SpawnSoundAtLocation(this, InSounds[TalkNum], GetOwner()->GetActorLocation());
		DialogueSoundComp->OnAudioFinished.AddDynamic(this, &UDialogueComponent::OnTalkEnd);
	}
	else if (!NoneSoundTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(NoneSoundTimer, this, &UDialogueComponent::OnTalkEnd, 2.0f);
	}
	else
	{
		OnTalkEnd();
	}
}

void UDialogueComponent::PlayDialogueSound(USoundBase* InSound)
{
	if (InSound && !DialogueSoundComp)
	{
		DialogueSoundComp = UGameplayStatics::SpawnSoundAtLocation(this, InSound, GetOwner()->GetActorLocation());
		DialogueSoundComp->OnAudioFinished.AddDynamic(this, &UDialogueComponent::CheckAction);
	}
	else if (!NoneSoundTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(NoneSoundTimer, this, &UDialogueComponent::CheckAction, 2.0f);
	}
	else
	{
		CheckAction();
	}
}

void UDialogueComponent::DeleteSoundAndTimer()
{
	if (DialogueSoundComp)
	{
		DialogueSoundComp->OnAudioFinished.RemoveAll(this);
		DialogueSoundComp->Stop();
		DialogueSoundComp->DestroyComponent();
		DialogueSoundComp = nullptr;
	}

	if (NoneSoundTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(NoneSoundTimer);
	}
}