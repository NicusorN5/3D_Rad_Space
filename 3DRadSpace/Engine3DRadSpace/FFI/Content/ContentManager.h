#pragma once
#include "IAsset.h"

typedef void* E3DRSP_ContentManager;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CONTENT_EXPORT E3DRSP_IAsset E3DRSP_ContentManager_Load(
		E3DRSP_ContentManager content, 
		const E3DRSP_UUID* uuid, 
		const char* path,
		unsigned* id
	);

	E3DRSP_CONTENT_EXPORT void E3DRSP_ContentManager_Reload(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_CONTENT_EXPORT void E3DRSP_ContentManager_Remove(E3DRSP_ContentManager content, unsigned id);
	E3DRSP_CONTENT_EXPORT void E3DRSP_ContentManager_Clear(E3DRSP_ContentManager content);
	E3DRSP_CONTENT_EXPORT size_t E3DRSP_ContentManager_Count(E3DRSP_ContentManager content);
#ifdef __cplusplus
}
#endif