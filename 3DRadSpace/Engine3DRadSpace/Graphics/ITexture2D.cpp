#include "ITexture2D.hpp"
#include "ITexture2D.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

E3DRSP_Point E3DRSP_ITexture2D_Size(E3DRSP_ITexture2D texture)
{
	auto size = reinterpret_cast<ITexture2D*>(texture)->Size();
	return E3DRSP_Point{ size.X, size.Y };
}

unsigned E3DRSP_ITexture2D_Width(E3DRSP_ITexture2D texture)
{
	return reinterpret_cast<ITexture2D*>(texture)->Width();
}

unsigned E3DRSP_ITexture2D_Height(E3DRSP_ITexture2D texture)
{
	return reinterpret_cast<ITexture2D*>(texture)->Height();
}

void* E3DRSP_ITexture2D_GetViewHandle(E3DRSP_ITexture2D texture)
{
	return reinterpret_cast<ITexture2D*>(texture)->GetViewHandle();
}

E3DRSP_ITexture2D E3DRSP_ITexture2D_CreateStaging(E3DRSP_ITexture2D texture)
{
	auto stagingTexture = reinterpret_cast<ITexture2D*>(texture)->CreateStaging();
	return static_cast<E3DRSP_ITexture2D>(stagingTexture.release());
}

void E3DRSP_ITexture2D_SaveToFile(E3DRSP_ITexture2D texture, const char* path)
{
	reinterpret_cast<ITexture2D*>(texture)->SaveToFile(std::filesystem::path(path));
}