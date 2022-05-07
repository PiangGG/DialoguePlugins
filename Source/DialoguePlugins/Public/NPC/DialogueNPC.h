// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/InteractiveInterface.h"
#include "DialogueNPC.generated.h"

UCLASS()
class DIALOGUEPLUGINS_API ADialogueNPC : public APawn,public IInteractiveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADialogueNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual const EInteractiveType& GetInteractiveType() override;
	virtual void Trigger() override;

private:

	UPROPERTY(EditAnywhere, meta = (DisplayName = "交互类型"))
	EInteractiveType Type;
};
