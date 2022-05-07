// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractionWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIALOGUEPLUGINS_API IInteractionWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void DeleteBrowseActor();

	virtual void DeleteBrowseWidget();

	virtual void UpdateMission();
};
