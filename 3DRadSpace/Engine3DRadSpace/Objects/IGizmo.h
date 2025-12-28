#pragma once
#include "IObject.h"

typedef void* E3DRSP_IGizmo;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_OBJECTS_GIZMOS_EXPORT E3DRSP_IObject E3DRSP_IGizmo_GetObject(E3DRSP_IGizmo gizmo);
	E3DRSP_OBJECTS_GIZMOS_EXPORT void E3DRSP_IGizmo_SetObject(E3DRSP_IGizmo gizmo, E3DRSP_IObject obj);

	E3DRSP_OBJECTS_GIZMOS_EXPORT bool E3DRSP_IGizmo_IsSelected(E3DRSP_IGizmo gizmo);
	E3DRSP_OBJECTS_GIZMOS_EXPORT void E3DRSP_IGizmo_SetSelection(E3DRSP_IGizmo gizmo, bool selected);

	E3DRSP_OBJECTS_GIZMOS_EXPORT bool E3DRSP_IGizmo_Is3DRenderingAllowed(E3DRSP_IGizmo gizmo);
	E3DRSP_OBJECTS_GIZMOS_EXPORT void E3DRSP_IGizmo_Set3DRenderingAllowed(E3DRSP_IGizmo gizmo, bool allow3D);

	E3DRSP_OBJECTS_GIZMOS_EXPORT bool E3DRSP_IGizmo_Is2DRenderingAllowed(E3DRSP_IGizmo gizmo);
	E3DRSP_OBJECTS_GIZMOS_EXPORT void E3DRSP_IGizmo_Set2DRenderingAllowed(E3DRSP_IGizmo gizmo, bool allow2D);

	E3DRSP_OBJECTS_GIZMOS_EXPORT bool E3DRSP_IGizmo_IsUpdatingAllowed(E3DRSP_IGizmo gizmo);
	E3DRSP_OBJECTS_GIZMOS_EXPORT void E3DRSP_IGizmo_SetUpdatingAllowed(E3DRSP_IGizmo gizmo, bool allowUpdate);

	E3DRSP_OBJECTS_GIZMOS_EXPORT void E3DRSP_IGizmo_Destroy(E3DRSP_IGizmo gizmo);
#ifdef __cplusplus
}
#endif