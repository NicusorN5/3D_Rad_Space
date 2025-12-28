#include "IDrawable3D.hpp"
#include "IDrawable3D.h"

using namespace Engine3DRadSpace;

void E3DRSP_IDrawable3D_Draw3D(E3DRSP_IDrawable3D drawable)
{
	static_cast<IDrawable3D*>(drawable)->Draw3D();
}

void E3DRSP_IDrawable3D_Destroy(E3DRSP_IDrawable3D drawable)
{
	delete static_cast<IDrawable3D*>(drawable);
}