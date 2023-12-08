// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"

#include "DialogueWidget.generated.h"

USTRUCT(BlueprintType,Blueprintable)
struct WHYDIALOGUE_API FDlgWidgetContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FText SpeakerName;

	UPROPERTY(BlueprintReadWrite)
	FText Context;

	UPROPERTY(BlueprintReadWrite)
	TArray<FText> Choices;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueContextChangedSignature, FDlgWidgetContext, DlgWidgetContext);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChoiceSignature, int, ChoiceIndex);

/**
 * 
 */

UCLASS()
class WHYDIALOGUE_API UDialogueWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UDialogueWidget();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDialogueContextChangedSignature DlgWidgetContextChangedEvent;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDialogueChoiceSignature DlgChoicedEvent;

protected:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnContextChanged(FDlgWidgetContext DlgWidgetContext);
};
