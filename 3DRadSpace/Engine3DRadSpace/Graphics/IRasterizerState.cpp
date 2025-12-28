#include "IRasterizerState.hpp"
#include "IRasterizerState.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void E3DRSP_IRasterizerState_Destroy(E3DRSP_IRasterizerState rasterizerState)
{
	delete static_cast<IRasterizerState*>(rasterizerState);
}