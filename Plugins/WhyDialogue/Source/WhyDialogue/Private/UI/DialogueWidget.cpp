﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueWidget.h"


UDialogueWidget::UDialogueWidget()
{
	DlgWidgetContextChangedEvent.AddDynamic(this, &UDialogueWidget::OnContextChanged);
}
