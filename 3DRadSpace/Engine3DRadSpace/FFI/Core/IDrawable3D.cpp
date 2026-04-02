#include "IDrawable3D.h"
#include "../../Core/IDrawable3D.hpp"

using namespace Engine3DRadSpace;

void E3DRSP_IDrawable3D_Draw3D(E3DRSP_IDrawable3D drawable)
{
	if (drawable == nullptr) return;
	static_cast<IDrawable3D*>(drawable)->Draw3D();
}

void E3DRSP_IDrawable3D_Destroy(E3DRSP_IDrawable3D drawable)
{
	assert(drawable != nullptr);
	delete static_cast<IDrawable3D*>(drawable);
}