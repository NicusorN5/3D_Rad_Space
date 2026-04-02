#include "SkyColor.h"
#include "../../../Objects/Impl/SkyColor.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

E3DRSP_SkyColor E3DRSP_SkyColor_Create()
{
	return new SkyColor();
}

E3DRSP_Color E3DRSP_SkyColor_Get(E3DRSP_SkyColor skyColor)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<SkyColor*>(skyColor)->Colour);
}

void E3DRSP_SkyColor_Set(E3DRSP_SkyColor skyColor, const E3DRSP_Color* color)
{
	static_cast<SkyColor*>(skyColor)->Colour = std::bit_cast<Math::Color>(*color);
}