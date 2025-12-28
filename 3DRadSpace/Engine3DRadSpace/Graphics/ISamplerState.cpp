#include "ISamplerState.hpp"
#include "ISamplerState.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void E3DRSP_ISamplerState_Destroy(E3DRSP_ISamplerState samplerState)
{
	delete static_cast<ISamplerState*>(samplerState);
}