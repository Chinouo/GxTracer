// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GxTracerHost.h"
#include "Modules/ModuleManager.h"
#include "RenderPreviewEditor.h"
#include "GxTracerPreviewEditor.h"

class FGxTracerKitModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void CreateMainMainBarEntry();
	
	
private:
	TSharedPtr<FRenderPreviewEditor> RenderPreviewEditor;
	TSharedPtr<FGxTracerPreviewEditor> PreviewEditor;
	TSharedPtr<FGxTracerHost> DebugHost;
};
