#include "GxTracerManager.h"
#include "GxTracerPreviewEditor.h"

void FGxTracerManager::StartUpManager()
{
	// call Get to pre initialize.
	TSharedRef<FGxTracerManager> Manager = Get();

}

void FGxTracerManager::ShutDownManager()
{
}

const TSharedRef<FGxTracerManager>& FGxTracerManager::Get()
{
	// Unreal Load Module is thread safe? FGlobalTabManager write like this.
	// Compiler may handle multi-thread.
	static const TSharedRef<FGxTracerManager> Instance = MakeShareable(new FGxTracerManager());
	return Instance;
}


TSharedRef<FGxTracerHost> FGxTracerManager::CreateGxTracerHost(FName HostId)
{
	if(Hosts.Contains(HostId))
	{
		UE_LOG(LogTemp, Warning, TEXT("GxTracerManager::CreateGxTracerHost: HostId already exist, return exist one."))
		return Hosts[HostId];
	}
	TSharedRef<FGxTracerHost> NewHost = MakeShared<FGxTracerHost>();
	Hosts.Add(HostId, NewHost);
	return NewHost;
}

void FGxTracerManager::DestroyGxTracerHost(FName HostId)
{
	check(false);// not impl.
	if(Hosts.Contains(HostId))
	{
				
	}
}
