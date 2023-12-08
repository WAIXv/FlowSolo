// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/DialogueNode_Sentence.h"

#include "DialogueSubsystem.h"
#include "FlowAsset.h"
#include "UI/DialogueWidget.h"

const FString UDialogueNode_Sentence::Continue = TEXT("Continue");

UDialogueNode_Sentence::UDialogueNode_Sentence(const FObjectInitializer& ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Dialogue");
#endif
	RefreshOutputs();
}

void UDialogueNode_Sentence::ExecuteInput(const FName& PinName)
{
	if (const auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>())
	{
		const auto Widget = Subsystem->ShowDialogueWidget(SpeakerName, Sentence, Choices);
		if (Choices.IsEmpty())
		{
			Subsystem->ContinuePressedEvent.AddDynamic(this, &UDialogueNode_Sentence::OnContinue);
		}
		else
		{
			Widget->DlgChoicedEvent.AddDynamic(this, &UDialogueNode_Sentence::OnChoiced);
		}
	}
}

#if WITH_EDITOR

#endif

void UDialogueNode_Sentence::FixNode(UEdGraphNode* NewGraph)
{
	RefreshOutputs();
}

void UDialogueNode_Sentence::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UDialogueNode_Sentence, Choices))
	{
		RefreshOutputs();
		OnReconstructionRequested.ExecuteIfBound();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UDialogueNode_Sentence::RefreshOutputs()
{
	OutputPins.Empty();

	if (Choices.IsEmpty())
	{
		OutputPins.Add({Continue});
		return;
	}
	
	for (auto Choice : Choices)
	{
		OutputPins.Add(Choice);
	}
}

void UDialogueNode_Sentence::OnContinue()
{
	TriggerFirstOutput(true);
}

void UDialogueNode_Sentence::OnChoiced(int ChoiceIndex)
{
	TriggerOutput(Choices[ChoiceIndex],true);
}

void UDialogueNode_Sentence::Cleanup()
{
	if (const auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>())
	{
		if (Choices.IsEmpty())
		{
			Subsystem->ContinuePressedEvent.RemoveDynamic(this, &UDialogueNode_Sentence::OnContinue);
		}
		else
		{
			Subsystem->GetDialogueWidget()->DlgChoicedEvent.RemoveDynamic(this, &UDialogueNode_Sentence::OnChoiced);
		}
	}
}
