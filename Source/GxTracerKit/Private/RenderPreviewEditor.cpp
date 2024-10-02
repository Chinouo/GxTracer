#include "RenderPreviewEditor.h"



const FName RenderPreviewEditorTabIds::EditorTab(TEXT("RenderPreviewEditor"));
const FName RenderPreviewEditorTabIds::Outliner(TEXT("RenderPreviewEditorOutliner"));
const FName RenderPreviewEditorTabIds::Viewport(TEXT("RenderPreviewEditorViewport"));
const FName RenderPreviewEditorTabIds::ActionPanel(TEXT("RenderPreviewEditorActionPanel"));

FRenderPreviewEditor::FRenderPreviewEditor()
{
}

void FRenderPreviewEditor::InitializeEditor()
{
	
	DefaultTabLayout = PerformLayout();
	EditorTabWidget = BuildEditorTab();
	TabManager = FGlobalTabmanager::Get()->NewTabManager(EditorTabWidget.ToSharedRef());
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(RenderPreviewEditorTabIds::EditorTab,
															  FOnSpawnTab::CreateRaw(this,
															  &FRenderPreviewEditor::OnSpawnRenderPreviewEditorTab));
	RegisterRenderPreviewEditorTabs();

	PreviewViewport = MakeShared<FTexturePreviewViewport>();
	PreviewViewport->Initialize();

}

void FRenderPreviewEditor::RegisterRenderPreviewEditorTabs()
{
	// Sub tabs.
	TabManager->RegisterTabSpawner(RenderPreviewEditorTabIds::ActionPanel,
	                               FOnSpawnTab::CreateRaw(this, &FRenderPreviewEditor::SpawnActionPanel));

	TabManager->RegisterTabSpawner(RenderPreviewEditorTabIds::Viewport, FOnSpawnTab::CreateRaw(this,
		                               &FRenderPreviewEditor::SpawnViewport));


	TabManager->RegisterTabSpawner(RenderPreviewEditorTabIds::Outliner,
		FOnSpawnTab::CreateRaw(this, &FRenderPreviewEditor::SpawnOutliner));
}

void FRenderPreviewEditor::UnRegisterRenderPreviewEditorTabs()
{
	TSharedRef<FGlobalTabmanager> Manager = FGlobalTabmanager::Get();
	Manager->UnregisterNomadTabSpawner(RenderPreviewEditorTabIds::EditorTab);
}

TSharedRef<SDockTab> FRenderPreviewEditor::BuildEditorTab()
{
	return SNew(SDockTab).TabRole(NomadTab);
}

TSharedRef<SDockTab> FRenderPreviewEditor::OnSpawnRenderPreviewEditorTab(const FSpawnTabArgs& Args)
{
	// EditorTabWidget->SetContent(
	// 	TabManager->RestoreFrom(DefaultTabLayout.ToSharedRef(), SNew(SWindow)).ToSharedRef()
	// 	);
	return SNew(SDockTab).TabRole(NomadTab)
		[
			TabManager->RestoreFrom(DefaultTabLayout.ToSharedRef(), Args.GetOwnerWindow()).ToSharedRef()
		];
	// if return cached widget, invoke will failed.
	return EditorTabWidget.ToSharedRef();
}


void FRenderPreviewEditor::InvokeRenderPreviewEditor()
{
	FGlobalTabmanager::Get()->TryInvokeTab(RenderPreviewEditorTabIds::EditorTab);
}

TSharedRef<FTabManager::FLayout> FRenderPreviewEditor::PerformLayout()
{
	TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("RenderPreviewEditorLayout")
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewStack()
				->AddTab(RenderPreviewEditorTabIds::ActionPanel, ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split(
					FTabManager::NewStack()
					->AddTab(RenderPreviewEditorTabIds::Viewport, ETabState::OpenedTab)
					->SetSizeCoefficient(.6f)
					->SetHideTabWell(true))
				->Split(
					FGlobalTabmanager::NewStack()
					->AddTab(RenderPreviewEditorTabIds::Outliner, ETabState::OpenedTab)
					->SetSizeCoefficient(.4f)
					->SetHideTabWell(false)
				)
			));
	return Layout;
}

TSharedRef<SDockTab> FRenderPreviewEditor::SpawnActionPanel(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab).TabRole(NomadTab)
		[
			SNew(STextBlock)
			.
			Text(FText::FromName(RenderPreviewEditorTabIds::ActionPanel))
		];
	
}

TSharedRef<SDockTab> FRenderPreviewEditor::SpawnViewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab).TabRole(NomadTab)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.Padding(0.5f, 25.0f)
			[
				SAssignNew(Viewport, SViewport)
				.ViewportInterface(PreviewViewport)
				.ViewportSize(FVector2d(80.0, 80.0))
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromName("HAPPY."))
			]
			
		];
}

TSharedRef<SDockTab> FRenderPreviewEditor::SpawnOutliner(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(NomadTab)
		[
			SNew(STextBlock)
			.
			Text(FText::FromName(RenderPreviewEditorTabIds::Outliner))
		];
}
