
#include "FTexturePreviewViewport.h"

#include "Engine/Texture2DDynamic.h"
#include "Templates/RefCounting.h"

FSlateShaderResource* FTexturePreviewViewport::GetViewportRenderTargetTexture() const
{
	// FSlateRenderTargetRHI;
	return SlateTextureRHI;
}

void FTexturePreviewViewport::Initialize()
{
	FTexture2DDynamicCreateInfo CreateInfo;
	CreateInfo.Filter = TF_Nearest;
	CreateInfo.Format = PF_R8G8B8A8;
	CreateInfo.bSRGB = false;

	
	
	Texture2D = UTexture2DDynamic::Create(800, 600, CreateInfo);
	
	//FTexture2DDynamicResource* Resource = Texture2D->GetResource();
	FTexture2DDynamicResource* Resource = static_cast<FTexture2DDynamicResource*>(Texture2D->GetResource());
	check(Resource != nullptr);

	// const int32 TextureSizeBytes = 800 * 600 * 4; // 800x600像素，每像素4字节
	// uint8* GreenPixelData = new uint8[TextureSizeBytes];
	//
	// // 填充整个缓冲区为绿色像素值 (ARGB顺序下绿色为0x00FF00FF，但此处直接按BGRA填充，即每四个字节一组为: 0, 255, 0, 255)
	// for (int32 i = 0; i < TextureSizeBytes; i += 4)
	// {
	// 	GreenPixelData[i + 0] = 0; // B
	// 	GreenPixelData[i + 1] = 255; // G
	// 	GreenPixelData[i + 2] = 128; // R
	// 	GreenPixelData[i + 3] = 255; // A
	// }

	const int32 TextureWidth = 800;
	const int32 TextureHeight = 600;
	const int32 PixelSize = 4; // 每像素4字节
	const int32 SquareSize = 100; // 棋盘格中每个方块的大小（以像素为单位）
	const int32 TextureSizeBytes = TextureWidth * TextureHeight * PixelSize;
	uint8* ChessboardPixelData = new uint8[TextureSizeBytes];

	// 填充棋盘格纹理
	for (int32 y = 0; y < TextureHeight; ++y)
	{
		for (int32 x = 0; x < TextureWidth; ++x)
		{
			int32 Index = (y * TextureWidth + x) * PixelSize;

			bool isLightGreen = ((x / SquareSize) + (y / SquareSize)) % 2 == 0; // 判断当前像素是否在浅绿色方块内

			if (isLightGreen)
			{
				// 浅绿色方块
				ChessboardPixelData[Index + 0] = 0; // B
				ChessboardPixelData[Index + 1] = 128; // G
				ChessboardPixelData[Index + 2] = 0; // R
				ChessboardPixelData[Index + 3] = 255; // A
			}
			else
			{
				// 深绿色方块
				ChessboardPixelData[Index + 0] = 0; // B
				ChessboardPixelData[Index + 1] = 64; // G
				ChessboardPixelData[Index + 2] = 0; // R
				ChessboardPixelData[Index + 3] = 255; // A
			}
		}
	}

	// 更新纹理的代码与之前相同，这里不再重复列出...

	// 使用完毕后释放分配的内存
	delete[] ChessboardPixelData;
	
	ENQUEUE_RENDER_COMMAND(UpdateMyTexture)([this, ChessboardPixelData](FRHICommandListImmediate& RHICmdList)
	{
		FUpdateTextureRegion2D UpdateTextureRegion;
		UpdateTextureRegion.SrcX = 0;
		UpdateTextureRegion.SrcY = 0;
		UpdateTextureRegion.DestX = 0;
		UpdateTextureRegion.DestY = 0;
		UpdateTextureRegion.Width = 800;
		UpdateTextureRegion.Height = 600;
		
		FTexture2DDynamicResource* Resource = static_cast<FTexture2DDynamicResource*>(Texture2D->GetResource());

		RHICmdList.UpdateTexture2D(Resource->GetTexture2DRHI()->GetTexture2D(), 0, UpdateTextureRegion, 800*4, ChessboardPixelData);
	});

	SlateTextureRHI = new FSlateRenderTargetRHI(Resource->GetTexture2DRHI(), Texture2D->SizeX, Texture2D->SizeY);
	
}

FIntPoint FTexturePreviewViewport::GetSize() const
{
	return FIntPoint(80, 60);
}

bool FTexturePreviewViewport::RequiresVsync() const
{
	return true;
}
