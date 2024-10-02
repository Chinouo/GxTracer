#pragma once

#include "Rendering/RenderingCommon.h"
#include "Slate/SlateTextures.h"
#include "Templates/RefCounting.h"

class FTexturePreviewViewport : public ISlateViewport
{
public:
	virtual FSlateShaderResource* GetViewportRenderTargetTexture() const override;
	void Initialize();
	virtual FIntPoint GetSize() const override;
	virtual bool RequiresVsync() const override;

private:
	FSlateRenderTargetRHI* RenderTargetRHI;
	UTexture2DDynamic* Texture2D;

	FSlateRenderTargetRHI* SlateTextureRHI;
	FTextureRenderTarget2DResource* RenderTarget2DResource;
	
};

class FTestViewportClient : FCommonViewportClient
{
	
};

class FTestViewport : public FViewport
{
public:
	virtual void* GetWindow() override;
	virtual void MoveWindow(int32 NewPosX, int32 NewPosY, int32 NewSizeX, int32 NewSizeY) override;
	virtual void Destroy() override;
	virtual bool SetUserFocus(bool bFocus) override;
	virtual bool KeyState(FKey Key) const override;
	virtual int32 GetMouseX() const override;
	virtual int32 GetMouseY() const override;
	virtual void GetMousePos(FIntPoint& MousePosition, const bool bLocalPosition) override;
	virtual void SetMouse(int32 x, int32 y) override;
	virtual void ProcessInput(float DeltaTime) override;
	virtual FVector2D VirtualDesktopPixelToViewport(FIntPoint VirtualDesktopPointPx) const override;
	virtual FIntPoint ViewportToVirtualDesktopPixel(FVector2D ViewportCoordinate) const override;
	virtual void InvalidateDisplay() override;
	virtual FViewportFrame* GetViewportFrame() override;
};