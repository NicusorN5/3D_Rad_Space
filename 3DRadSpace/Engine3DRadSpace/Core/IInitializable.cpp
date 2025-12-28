#include "IInitializable.hpp"
#include "IInitializable.h"

using namespace Engine3DRadSpace;

void E3DRSP__Initialize(E3DRSP_IInitializable instance)
{
	static_cast<IInitializable*>(instance)->Initialize();
}

void E3DRSP_IInitializable_Destroy(E3DRSP_IInitializable instance)
{
	delete static_cast<IInitializable*>(instance);
}
