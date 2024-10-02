#pragma once
#include "GxTracerHost.h"

// Standalone window for view ray tracing result, modify object detail etc.
// Editor class do not store any state of host.
class FGxTracerPreviewEditor
{
public:
	static const FName GxTracerPreviewEditorId;
	static const FName ViewportTabId;
	static const FName ToolbarTabId;
	static const FName PanelTabId;
public:
	FGxTracerPreviewEditor(const TSharedRef<FGxTracerHost>& InOwnerHost);
	void InitializeEditor();
	void DestoryEditor();
	void InvokeEditor();
private:
	TSharedRef<SDockTab> SpawnGxTracerPreviewEditorTab();
	void BuildWidgetInternal();
	TSharedRef<FTabManager::FLayout> PerformLayout();
	
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager);
	void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager);

	// Spawn sub tabs callback.
	TSharedRef<SDockTab> OnSpawnToolbar(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> OnSpawnViewport(const FSpawnTabArgs& Args);
	
	// Viewport for scene rendering preview.
	TSharedPtr<SViewport> SViewportWidget;
	TSharedPtr<FSceneViewport> PreviewRenderingSceneViewport;

	// Tab manager to store layout.
	TSharedPtr<FTabManager> TabManager;

	// Default window layout.
	TSharedPtr<FTabManager::FLayout> EditorLayout;

	// Identify of a tab.
	FName TabName;

	// The host we associated.
	TWeakPtr<FGxTracerHost> OwnerHost;

	//
	bool bEditorInitialized;
};
