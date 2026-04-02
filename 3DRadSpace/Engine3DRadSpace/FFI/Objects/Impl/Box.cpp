#include "Box.h"
#include "../../../Objects/Impl/Box.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_OBox E3DRSP_OBox_Create()
{
	return new Box();
}

E3DRSP_Color E3DRSP_OBox_GetColor(E3DRSP_OBox box)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Box*>(box)->Colour);
}

void E3DRSP_OBox_SetColor(E3DRSP_OBox box, const E3DRSP_Color* color)
{
	static_cast<Box*>(box)->Colour = std::bit_cast<Color>(*color);
}