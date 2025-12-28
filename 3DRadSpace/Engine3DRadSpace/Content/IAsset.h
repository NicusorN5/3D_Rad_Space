#pragma once
#include "../Reflection/UUID.h"
#include "../Core/Libs.h"

typedef void* E3DRSP_IAsset;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_CONTENT_EXPORT E3DRSP_UUID E3DRSP_IAsset_GetUUID(E3DRSP_IAsset asset);
	E3DRSP_CONTENT_EXPORT const char* E3DRSP_IAsset_FileExtension(E3DRSP_IAsset asset);
	E3DRSP_CONTENT_EXPORT void E3DRSP_IAsset_Destroy(E3DRSP_IAsset asset);
#ifdef __cplusplus
}
#endif