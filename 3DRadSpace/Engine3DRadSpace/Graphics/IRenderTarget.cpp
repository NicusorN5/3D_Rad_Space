#include "IRenderTarget.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void* E3DRSP_IRenderTarget_RenderTargetHandle(E3DRSP_IRenderTarget renderTarget)
{
	return reinterpret_cast<IRenderTarget*>(renderTarget)->RenderTargetHandle();
}

void E3DRSP_IRenderTarget_Destroy(E3DRSP_IRenderTarget renderTarget)
{
	delete reinterpret_cast<IRenderTarget*>(renderTarget);
}