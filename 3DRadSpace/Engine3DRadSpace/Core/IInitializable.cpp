#include "IInitializable.hpp"
#include "IInitializable.h"

using namespace Engine3DRadSpace;

void E3DRSP_IInitializable_Initialize(E3DRSP_IInitializable instance)
{
	if (instance == nullptr) return;
	static_cast<IInitializable*>(instance)->Initialize();
}

void E3DRSP_IInitializable_Destroy(E3DRSP_IInitializable instance)
{
	assert(instance != nullptr);
	delete static_cast<IInitializable*>(instance);
}
