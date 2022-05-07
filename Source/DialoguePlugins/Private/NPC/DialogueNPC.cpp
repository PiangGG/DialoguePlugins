// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/DialogueNPC.h"


// Sets default values
ADialogueNPC::ADialogueNPC():Type(EInteractiveType::NPC)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADialogueNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADialogueNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

const EInteractiveType& ADialogueNPC::GetInteractiveType()
{
	return Type;
}

void ADialogueNPC::Trigger()
{
	Execute_BP_Trigger(this);
}

