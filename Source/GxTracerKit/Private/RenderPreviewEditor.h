#pragma once

#include "Widgets/SViewport.h"
#include "FTexturePreviewViewport.h"

class RenderPreviewEditorTabIds{
public:
	static const FName EditorTab;
	
	static const FName ActionPanel;
	static const FName Viewport;
	static const FName Outliner;
};

class FRenderPreviewEditor
{
public:
	FRenderPreviewEditor();
	
	void InitializeEditor();
	
	
	TSharedRef <SDockTab> OnSpawnRenderPreviewEditorTab(const FSpawnTabArgs& Args);
	void InvokeRenderPreviewEditor();

	TSharedRef<FTabManager::FLayout> PerformLayout();
private:
	void RegisterRenderPreviewEditorTabs();
	void UnRegisterRenderPreviewEditorTabs();

	TSharedRef<SDockTab> BuildEditorTab();
	
	TSharedRef<SDockTab> SpawnActionPanel(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnViewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnOutliner(const FSpawnTabArgs& Args);

	// Editor tab action callback.
	void OnCloseEditorTab();

	// Internal Tab Manger, Make sure non-null after initialized. 
	TSharedPtr<FTabManager> TabManager;

	// Make sure non-null after initialized.
	TSharedPtr<SDockTab> EditorTabWidget;
	
	// Default Layout. Make sure non-null after initialized.
	TSharedPtr<FTabManager::FLayout> DefaultTabLayout;

	TSharedPtr<SViewport> Viewport;

	TSharedPtr<FTexturePreviewViewport> PreviewViewport;
	
};
