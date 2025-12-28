#include "IDepthStencilState.hpp"
#include "IDepthStencilState.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

unsigned int E3DRSP_IDepthStencilState_StencilRef(E3DRSP_IDepthStencilState depthStencilState)
{
	return reinterpret_cast<IDepthStencilState*>(depthStencilState)->StencilRef();
}