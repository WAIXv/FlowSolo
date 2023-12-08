// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "UI/DialogueWidget.h"


void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
	
	ContinuePressedEvent.AddDynamic(this, &UDialogueSubsystem::OnContinuePressed);
	EndPressedEvent.AddDynamic(this, &UDialogueSubsystem::CloseDialogueWidget);
}

UDialogueWidget* UDialogueSubsystem::ShowDialogueWidget(FText SpeakerName, FText Content,
                                                        TArray<FText> Choices)
{
	if (!DialogueWidget) return nullptr;
	
	DialogueWidget->DlgWidgetContextChangedEvent.Broadcast({SpeakerName, Content, Choices});
	const auto LocalPlayerController = GetWorld()->GetFirstPlayerController();
	check(LocalPlayerController)
	LocalPlayerController->DisableInput(LocalPlayerController);
	LocalPlayerController->SetShowMouseCursor(true);
	DialogueWidget->SetUserFocus(LocalPlayerController);

	if (!DialogueWidget->IsInViewport())
		DialogueWidget->AddToViewport();

	return DialogueWidget.Get();
}

void UDialogueSubsystem::CloseDialogueWidget()
{
	if (!DialogueWidget) return;

	const auto LocalPlayerController = GetWorld()->GetFirstPlayerController();
	check(LocalPlayerController)
	LocalPlayerController->EnableInput(LocalPlayerController);
	LocalPlayerController->SetShowMouseCursor(false);

	DialogueWidget->RemoveFromParent();
}
