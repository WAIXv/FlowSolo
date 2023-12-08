// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowComponent.h"

#include "DialogueComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WHYDIALOGUE_API UDialogueComponent : public UFlowComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

	UFUNCTION(BlueprintCallable)
	void RefreshDialogueContext(FText SpeakerName, FText Sentence, TArray<FText> Choices);
};
