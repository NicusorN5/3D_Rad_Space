#include "ILoadable.hpp"
#include "ILoadable.h"

using namespace Engine3DRadSpace;

void E3DRSP_ILoadable_Load(E3DRSP_ILoadable obj)
{
	if (obj == nullptr) return;
	static_cast<ILoadable*>(obj)->Load();
}

void E3DRSP_ILoadable_Load2(E3DRSP_ILoadable obj, const char* path)
{
	if (obj == nullptr) return;
	static_cast<ILoadable*>(obj)->Load(std::filesystem::path(path));
}

void E3DRSP_ILoadable_Destroy(E3DRSP_ILoadable obj)
{
	assert(obj != nullptr);
	delete static_cast<ILoadable*>(obj);
}