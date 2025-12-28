#include "IDepthStencilBuffer.hpp"
#include "IDepthStencilBuffer.h"
#include "ITexture2D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void* E3DRSP_IDepthStencilBuffer_GetDepthTextureHandle(E3DRSP_IDepthStencilBuffer depthStencilBuffer)
{
	return reinterpret_cast<IDepthStencilBuffer*>(depthStencilBuffer)->GetDepthTextureHandle();
}

E3DRSP_ITexture2D* E3DRSP_IDepthStencilBuffer_GetDepthTexture(E3DRSP_IDepthStencilBuffer depthStencilBuffer)
{
	return reinterpret_cast<E3DRSP_ITexture2D*>(reinterpret_cast<IDepthStencilBuffer*>(depthStencilBuffer)->GetDepthTexture());
}

E3DRSP_ITexture2D* E3DRSP_IDepthStencilBuffer_CloneDepthTexture(E3DRSP_IDepthStencilBuffer depthStencilBuffer)
{
	auto texture = reinterpret_cast<IDepthStencilBuffer*>(depthStencilBuffer)->CloneDepthTexture();
	return reinterpret_cast<E3DRSP_ITexture2D*>(texture.release());
}

void E3DRSP_IDepthStencilBuffer_Destroy(E3DRSP_IDepthStencilBuffer depthStencilBuffer)
{
	delete reinterpret_cast<IDepthStencilBuffer*>(depthStencilBuffer);
}