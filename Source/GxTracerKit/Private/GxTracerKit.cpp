// Copyright Epic Games, Inc. All Rights Reserved.

#include "GxTracerKit.h"

#include "GxTracerPreviewEditor.h"
#include "RenderPreviewEditor.h"
#include "ToolMenu.h"
#include "GxTracerManager.h"

#define LOCTEXT_NAMESPACE "FGxTracerKitModule"

void FGxTracerKitModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	CreateMainMainBarEntry();
	//FGxTracerManager::StartUpManager();

	UE_LOG(LogTemp, Log, TEXT("GxTracer Module Startup."))
}

void FGxTracerKitModule::ShutdownModule()
{
	FGxTracerManager::ShutDownManager();
	
	if(RenderPreviewEditor.IsValid())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RenderPreviewEditorTabIds::EditorTab);
		RenderPreviewEditor.Reset();
	}
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Log, TEXT("GxTracer Module ShutDown."))
}


void FGxTracerKitModule::CreateMainMainBarEntry()
{
	// Create main menu bar entry.
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
	FToolMenuSection& Section = Menu->FindOrAddSection((NAME_None));
	FToolMenuEntry& Entry = Section.AddSubMenu(
		"GxTracerKitMenu",
		LOCTEXT("GxTracerKitMenu", "GxTracerKit"),
		LOCTEXT("GxTracerKitMenuToolTip", ""),
		FNewToolMenuChoice());
	Entry.InsertPosition = FToolMenuInsert("Help", EToolMenuInsertType::After);

	// Register and create menu section.
	UToolMenu* KitsMenu = UToolMenus::Get()->RegisterMenu("LevelEditor.MainMenu.GxTracerKitMenu");
	FToolMenuSection& KitsOpenSection = KitsMenu->AddSection("GxTracerKitOpenSection", FText::FromString("Open"));

	// Create RenderPreviewEditor Entry.
	KitsOpenSection.AddMenuEntry(
		"RenderPreviewEditor",
		LOCTEXT("GxTracerKitPrewviewWindow", "PrewviewWindow"),
		LOCTEXT("", ""),
		FSlateIcon(),
		FToolUIActionChoice(FExecuteAction::CreateLambda([this]()
		{
			if(!RenderPreviewEditor.IsValid())
			{
				RenderPreviewEditor = MakeShared<FRenderPreviewEditor>();
				RenderPreviewEditor->InitializeEditor();
			}
			RenderPreviewEditor->InvokeRenderPreviewEditor();
		})));

	// GxTracerPreviewEditor Entry.
	KitsOpenSection.AddMenuEntry(
		"GxTracerPreviewEditor",
		LOCTEXT("GxTracerPreviewEditor", "PreviewEditor"),
		LOCTEXT("", ""),
		FSlateIcon(),
		FToolUIActionChoice(FExecuteAction::CreateLambda([this]()
		{
			if(!DebugHost.IsValid())
			{
				DebugHost = MakeShareable(new FGxTracerHost());
				PreviewEditor = MakeShareable(new FGxTracerPreviewEditor(DebugHost.ToSharedRef()));
				PreviewEditor->InitializeEditor();
			}
			PreviewEditor->InvokeEditor();
			
		})));
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGxTracerKitModule, GxTracerKit)