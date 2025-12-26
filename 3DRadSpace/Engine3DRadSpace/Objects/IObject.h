#pragma once
#include "../Reflection/UUID.h"
#include "../Graphics/IGraphicsDevice.h"

typedef void* E3DRSP_IObject;

#ifdef __cplusplus
extern "C" {
#endif
E3DRSP_UUID E3DRSP_IObject_GetUUID(E3DRSP_IObject object);


#ifdef __cplusplus
}
#endif