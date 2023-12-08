// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSubsystem.generated.h"

class UDialogueWidget;
class UDialogueComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueContinueSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueEndSignature);

UCLASS(BlueprintType, Blueprintable, Abstract)
class WHYDIALOGUE_API UDialogueSubsystem : public UGameInstanceSubsystem
{
private:
	GENERATED_BODY()

protected:
	TObjectPtr<UDialogueWidget> DialogueWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	virtual UDialogueWidget* ShowDialogueWidget(FText SpeakerName, FText Content, TArray<FText> Choices);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void ContinueDialogue(UDialogueComponent* DialogueComponent, int ChoiceIndex);

	UFUNCTION(BlueprintCallable)
	void CloseDialogueWidget();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDialogueContinueSignature ContinuePressedEvent;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnContinuePressed();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDialogueEndSignature EndPressedEvent;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEndPressed();

	UFUNCTION(BlueprintCallable)
	UDialogueWidget* GetDialogueWidget() { return DialogueWidget; }

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UDialogueComponent> CurDialogueTarget;
};
