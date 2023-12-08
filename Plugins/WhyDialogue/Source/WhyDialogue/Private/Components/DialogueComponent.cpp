// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DialogueComponent.h"


UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDialogueComponent::RefreshDialogueContext(FText SpeakerName, FText Sentence, TArray<FText> Choices)
{
	
}
