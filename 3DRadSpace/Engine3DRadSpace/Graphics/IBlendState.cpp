#include "IBlendState.hpp"
#include "IBlendState.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_Color E3DRSP_IBlendState_BlendFactor(E3DRSP_IBlendState blendState)
{
	auto color = reinterpret_cast<IBlendState*>(blendState)->BlendFactor();

	return E3DRSP_Color{ color.R, color.G, color.B, color.A };
}

unsigned int E3DRSP_IBlendState_SampleMask(E3DRSP_IBlendState blendState)
{
	return reinterpret_cast<IBlendState*>(blendState)->SampleMask();
}

void E3DRSP_IBlendState_Destroy(E3DRSP_IBlendState blendState)
{
	delete reinterpret_cast<IBlendState*>(blendState);
}