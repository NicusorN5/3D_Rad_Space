#pragma once
#include "../Reflection/UUID.h"
#include "../Graphics/IGraphicsDevice.h"

typedef void* E3DRSP_IObject;
typedef void* E3DRSP_IGizmo;
typedef void* E3DRSP_IGame;

#ifdef __cplusplus
extern "C" {
#endif
	E3DRSP_FFI_EXPORT E3DRSP_UUID E3DRSP_IObject_GetUUID(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT E3DRSP_IGizmo E3DRSP_IObject_GetGizmo(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT E3DRSP_IGraphicsDevice E3DRSP_IObject_GetGraphicsDeviceHandle(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT E3DRSP_IGame E3DRSP_IObject_GetGame(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT void E3DRSP_IObject_Enable(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT void E3DRSP_IObject_Disable(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT bool E3DRSP_IObject_Switch(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT bool E3DRSP_IObject_IsEnabled(E3DRSP_IObject object);

	E3DRSP_FFI_EXPORT void E3DRSP_IObject_Show(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT void E3DRSP_IObject_Hide(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT bool E3DRSP_IObject_SwitchVisibility(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT bool E3DRSP_IObject_IsVisible(E3DRSP_IObject object);

	E3DRSP_FFI_EXPORT const char* E3DRSP_IObject_GetName(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT void E3DRSP_IObject_SetName(E3DRSP_IObject object, const char* name);

	E3DRSP_FFI_EXPORT void* E3DRSP_IObject_Children(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT E3DRSP_IObject E3DRSP_IObject_GetChild(E3DRSP_IObject object, size_t idxChild);
	E3DRSP_FFI_EXPORT size_t E3DRSP_IObject_GetChildrenCount(E3DRSP_IObject object);

	E3DRSP_FFI_EXPORT E3DRSP_IObject E3DRSP_IObject_GetParent(E3DRSP_IObject object);
	E3DRSP_FFI_EXPORT void E3DRSP_IObject_SetParent(E3DRSP_IObject object, E3DRSP_IObject newParent);
#ifdef __cplusplus
}
#endif