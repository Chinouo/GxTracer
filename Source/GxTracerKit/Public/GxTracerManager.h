#pragma once

#include "GxTracerPreviewEditor.h"
#include "GxTracerHost.h"

// Singleton for manager GxTracer state, toolkits...
class FGxTracerManager
{
public:
	static void StartUpManager();
	static void ShutDownManager();
	static const TSharedRef<FGxTracerManager>& Get();
	
	TSharedRef<FGxTracerPreviewEditor> CreateAndInitEditor(FName TabName);

	// If Host Id already exist. return it.
	TSharedRef<FGxTracerHost> CreateGxTracerHost(FName HostId);
	void DestroyGxTracerHost(FName HostId);
	
private:
	// All GxTracer hosts.
	TMap<FName, TSharedRef<FGxTracerHost>> Hosts;
	
	// current only support one preview editor instance.
	TSharedPtr<FGxTracerPreviewEditor> OpenedPreviewEditor;

	// manage created editor.
	TMap<FName, TSharedRef<FGxTracerPreviewEditor>> PreviewEditors;
};
