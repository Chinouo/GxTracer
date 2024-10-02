// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GxTracerPreviewEditorClient.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SViewport.h"

/**
 * 
 */
class GXTRACERKIT_API SGxTracerPreviewEditorViewport : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGxTracerPreviewEditorViewport)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<SViewport> ViewportWidget;
	TSharedPtr<FSceneViewport> Viewport;
	TSharedPtr<FGxTracerPreviewEditorClient> ViewportClient;
};
