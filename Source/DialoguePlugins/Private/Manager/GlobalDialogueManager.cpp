// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GlobalDialogueManager.h"

EDialogueState UGlobalDialogueManager::DialogueState = EDialogueState::NONE;

const EDialogueState& UGlobalDialogueManager::GetDialogueState()
{
	return DialogueState;
}

void UGlobalDialogueManager::SetDialogueState(EDialogueState InState)
{
	DialogueState = InState;
}