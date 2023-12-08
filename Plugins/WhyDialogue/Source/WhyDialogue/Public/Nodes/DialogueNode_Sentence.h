// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DialogueComponent.h"
#include "Engine/DataAsset.h"
#include "Nodes/FlowNode.h"
#include "DialogueNode_Sentence.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, Blueprintable)
class WHYDIALOGUE_API USentenceSpeakerContext : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="Dialogue")
	FGameplayTag SpeakerTag;

	
};

UCLASS()
class WHYDIALOGUE_API UDialogueNode_Sentence : public UFlowNode
{
	GENERATED_BODY()

	friend UDialogueComponent;

protected:
	UPROPERTY(EditAnywhere, Category=Dialogue)
	FGameplayTag IdentityTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Dialogue)
	FText SpeakerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Dialogue)
	FText Sentence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Dialogue)
	TArray<FText> Choices;
	

public:
	
	static const FString Continue;

	explicit UDialogueNode_Sentence(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual void FixNode(UEdGraphNode* NewGraph) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:

	void RefreshOutputs();

	UFUNCTION()
	void OnContinue();

	UFUNCTION()
	void OnChoiced(int ChoiceIndex);

	virtual void Cleanup() override;
	
};
