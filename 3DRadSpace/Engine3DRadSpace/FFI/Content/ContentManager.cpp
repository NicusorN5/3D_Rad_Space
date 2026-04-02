#include "ContentManager.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

E3DRSP_IAsset E3DRSP_ContentManager_Load(E3DRSP_ContentManager content, const E3DRSP_UUID* uuid, const char* path, unsigned* id)
{
	if(content == nullptr) return nullptr;

	return static_cast<ContentManager*>(content)->Load(
		*reinterpret_cast<const Reflection::UUID*>(uuid),
		std::filesystem::path(path),
		id
	);
}

void E3DRSP_ContentManager_Reload(E3DRSP_ContentManager content, unsigned id)
{
	if(content == nullptr) return;
	static_cast<ContentManager*>(content)->Reload(id);
}

void E3DRSP_ContentManager_Remove(E3DRSP_ContentManager content, unsigned id)
{
	if(content == nullptr) return;
	static_cast<ContentManager*>(content)->RemoveAsset(id);
}

void E3DRSP_ContentManager_Clear(E3DRSP_ContentManager content)
{
	if(content == nullptr) return;
	static_cast<ContentManager*>(content)->Clear();
}

size_t E3DRSP_ContentManager_Count(E3DRSP_ContentManager content)
{
	if(content == nullptr) return 0;
	return static_cast<ContentManager*>(content)->Count();
}