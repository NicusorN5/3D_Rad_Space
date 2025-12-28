#include "IDrawable2D.hpp"
#include "IDrawable2D.h"

using namespace Engine3DRadSpace;

void E3DRSP_IDrawable2D_Draw2D(E3DRSP_IDrawable2D drawable)
{
	static_cast<IDrawable2D*>(drawable)->Draw2D();
}

void E3DRSP_IDrawable2D_Destroy(E3DRSP_IDrawable2D drawable)
{
	delete static_cast<IDrawable2D*>(drawable);
}