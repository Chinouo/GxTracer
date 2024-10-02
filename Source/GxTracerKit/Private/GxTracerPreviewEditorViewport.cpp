// Fill out your copyright notice in the Description page of Project Settings.


#include "GxTracerPreviewEditorViewport.h"
#include "SlateOptMacros.h"
#include "Slate/SceneViewport.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGxTracerPreviewEditorViewport::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(ViewportWidget, SViewport)
	];

	ViewportClient = MakeShareable(new FGxTracerPreviewEditorClient());
	Viewport = MakeShareable(new FSceneViewport(ViewportClient.Get(), ViewportWidget));
	ViewportWidget->SetViewportInterface(Viewport.ToSharedRef());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
