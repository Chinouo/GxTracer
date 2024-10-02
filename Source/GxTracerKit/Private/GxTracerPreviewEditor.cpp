#include "GxTracerPreviewEditor.h"

#include "GxTracerPreviewEditorViewport.h"

const FName FGxTracerPreviewEditor::GxTracerPreviewEditorId(TEXT("GxTracerPreviewEditor"));
const FName FGxTracerPreviewEditor::ViewportTabId(TEXT("GxTracerPreviewEditor_Viewport"));
const FName FGxTracerPreviewEditor::ToolbarTabId(TEXT("GxTracerPreviewEditor_Toolbar"));
const FName FGxTracerPreviewEditor::PanelTabId(TEXT("GxTracerPreviewEditor_Panel"));


FGxTracerPreviewEditor::FGxTracerPreviewEditor(const TSharedRef<FGxTracerHost>& InOwnerHost)
	: OwnerHost(InOwnerHost),
	  bEditorInitialized(false)
{
}


void FGxTracerPreviewEditor::InitializeEditor()
{
	BuildWidgetInternal();
	
	TSharedRef<SDockTab> NewMajorTab = SNew(SDockTab).TabRole(MajorTab);
	TabManager = FGlobalTabmanager::Get()->NewTabManager(NewMajorTab);
	
	EditorLayout = PerformLayout();
	RegisterTabSpawners(TabManager.ToSharedRef());
	bEditorInitialized = true;
}

void FGxTracerPreviewEditor::DestoryEditor()
{
	check(false);
}


void FGxTracerPreviewEditor::InvokeEditor()
{
	FGlobalTabmanager::Get()->InsertNewDocumentTab(
		"StandaloneToolkit",
		FTabManager::ESearchPreference::Type::RequireClosedTab,
		SpawnGxTracerPreviewEditorTab()
	);
}

TSharedRef<SDockTab> FGxTracerPreviewEditor::SpawnGxTracerPreviewEditorTab()
{
	return SNew(SDockTab)
		.TabRole(MajorTab)
		.Label(FText::FromName(TabName))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.Padding(6.0f)
			.MaxHeight(55.0f)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.MaxWidth(50.0f)
				[
					SNew(SButton)
				]
				+SHorizontalBox::Slot()
				.MaxWidth(50.0f)
				[
					SNew(SButton)
				]
				+SHorizontalBox::Slot()
				.MaxWidth(50.0f)
				[
					SNew(SButton)
				]
				
				
			]
			+SVerticalBox::Slot()
			[
				TabManager->RestoreFrom(EditorLayout.ToSharedRef(), nullptr).ToSharedRef()
			]
		];
}

void FGxTracerPreviewEditor::BuildWidgetInternal()
{
	// if(EditorLayout.IsValid())
	// TabManager->RestoreFrom(EditorLayout.ToSharedRef(), SNew(SWindow));
	//SAssignNew(SGxTracerPreviewEditorViewport, ViewportWidget);
}

TSharedRef<FTabManager::FLayout> FGxTracerPreviewEditor::PerformLayout()
{
	return FTabManager::NewLayout("GxTracerPreviewEditorLayout")
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewStack()
				->SetHideTabWell(true)
				->AddTab(ToolbarTabId, ETabState::OpenedTab)
				->SetSizeCoefficient(0.1f)
				
			)
			->Split(FTabManager::NewStack()
				->AddTab(ViewportTabId, ETabState::OpenedTab)
				->SetHideTabWell(false)
				->SetSizeCoefficient(0.9f)
			)
		);
}

void FGxTracerPreviewEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->RegisterTabSpawner(FGxTracerPreviewEditor::ToolbarTabId,
	                                 FOnSpawnTab::CreateRaw(this, &FGxTracerPreviewEditor::OnSpawnToolbar),
	                                 FCanSpawnTab());
	InTabManager->RegisterTabSpawner(FGxTracerPreviewEditor::ViewportTabId,
	                                 FOnSpawnTab::CreateRaw(this, &FGxTracerPreviewEditor::OnSpawnViewport),
	                                 FCanSpawnTab());
}

// TODO: When to call this fun?
void FGxTracerPreviewEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FGxTracerPreviewEditor::ToolbarTabId);
	InTabManager->UnregisterTabSpawner(FGxTracerPreviewEditor::ViewportTabId);
}

TSharedRef<SDockTab> FGxTracerPreviewEditor::OnSpawnToolbar(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(PanelTab)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(3.5f)
			[
				SNew(SButton)
				[
					SNew(SImage)
					.Image((FAppStyle::Get().GetBrush("Icons.sphere")))
				]
			]
			
		];
}

TSharedRef<SDockTab> FGxTracerPreviewEditor::OnSpawnViewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(PanelTab)
		[
			SNew(STextBlock).Text(FText::FromString("Viewport"))
		];
}
