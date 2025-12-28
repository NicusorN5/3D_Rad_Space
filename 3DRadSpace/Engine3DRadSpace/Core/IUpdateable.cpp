#include "IUpdateable.hpp"
#include "IUpdateable.h"

using namespace Engine3DRadSpace;

void E3DRSP_IUpdateable_Update(E3DRSP_IUpdateable instance)
{
	if (instance == nullptr) return;
	static_cast<IUpdateable*>(instance)->Update();
}

void E3DRSP_IUpdateable_Destroy(E3DRSP_IUpdateable instance)
{
	assert(instance != nullptr);
	delete static_cast<IUpdateable*>(instance);
}
