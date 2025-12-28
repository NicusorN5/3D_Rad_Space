#include "IAsset.hpp"
#include "IAsset.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

E3DRSP_UUID E3DRSP_IAsset_GetUUID(E3DRSP_IAsset asset)
{
	if (asset == nullptr) return {};
	auto uuid = static_cast<IAsset*>(asset)->GetUUID();

	E3DRSP_UUID r;
	memcpy_s(&r, sizeof(E3DRSP_UUID), &uuid, sizeof(Reflection::UUID));
	return r;
}

const char* E3DRSP_IAsset_FileExtension(E3DRSP_IAsset asset)
{
	if (asset == nullptr) return "";
	return static_cast<IAsset*>(asset)->FileExtension();
}

void E3DRSP_IAsset_Destroy(E3DRSP_IAsset asset)
{
	assert(asset != nullptr);
	delete static_cast<IAsset*>(asset);
}