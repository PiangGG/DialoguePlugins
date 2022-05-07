// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/InteractiveData.h"
#include "UObject/Interface.h"
#include "InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIALOGUEPLUGINS_API IInteractiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual const EInteractiveType& GetInteractiveType() = 0;
	virtual void Trigger() = 0;
	virtual void SetLight(bool bIsLight) {}

	virtual void SetTargetID(const FString& InID, const FString& InName) {}

	virtual AActor* GetInteractActor() { return nullptr; }
	virtual void GetInitiatorID(FString& OutID) {}
	virtual	void GetInitiatorName(FString& OutName) {}
	virtual void GetTargetName(FString& OutName) {}

	virtual void TriggerMultiInter() {}

	virtual void GetOpenID(FString& OutID) {}
	virtual void GetTargetID(FString& OutID) {}

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "获取OpenID"))
	void BP_GetOpenID(FString& OutID);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "触发交互接口"))
	void BP_Trigger();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "触发亮光"))
	void BP_Light(bool bIsLight);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "获取交互对象"))
	AActor* BP_GetInteractActor();
};
