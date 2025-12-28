#include "IGizmo.hpp"
#include "IGizmo.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

E3DRSP_IObject E3DRSP_IGizmo_GetObject(E3DRSP_IGizmo gizmo)
{
	return static_cast<E3DRSP_IObject>(static_cast<IGizmo*>(gizmo)->Object);
}

void E3DRSP_IGizmo_SetObject(E3DRSP_IGizmo gizmo, E3DRSP_IObject obj)
{
	static_cast<IGizmo*>(gizmo)->Object = static_cast<IObject*>(obj);
}

bool E3DRSP_IGizmo_IsSelected(E3DRSP_IGizmo gizmo)
{
	return static_cast<IGizmo*>(gizmo)->Selected;
}

void E3DRSP_IGizmo_SetSelection(E3DRSP_IGizmo gizmo, bool selected)
{
	static_cast<IGizmo*>(gizmo)->Selected = selected;
}

bool E3DRSP_IGizmo_Is3DRenderingAllowed(E3DRSP_IGizmo gizmo)
{
	return static_cast<IGizmo*>(gizmo)->Allow3DRendering;
}

void E3DRSP_IGizmo_Set3DRenderingAllowed(E3DRSP_IGizmo gizmo, bool allow3D)
{
	static_cast<IGizmo*>(gizmo)->Allow3DRendering = allow3D;
}

bool E3DRSP_IGizmo_Is2DRenderingAllowed(E3DRSP_IGizmo gizmo)
{
	return static_cast<IGizmo*>(gizmo)->Allow2DRendering;
}

void E3DRSP_IGizmo_Set2DRenderingAllowed(E3DRSP_IGizmo gizmo, bool allow2D)
{
	static_cast<IGizmo*>(gizmo)->Allow2DRendering = allow2D;
}

bool E3DRSP_IGizmo_IsUpdatingAllowed(E3DRSP_IGizmo gizmo)
{
	return static_cast<IGizmo*>(gizmo)->AllowUpdating;
}

void E3DRSP_IGizmo_SetUpdatingAllowed(E3DRSP_IGizmo gizmo, bool allowUpdate)
{
	static_cast<IGizmo*>(gizmo)->AllowUpdating = allowUpdate;
}

void E3DRSP_IGizmo_Destroy(E3DRSP_IGizmo gizmo)
{
	delete static_cast<IGizmo*>(gizmo);
}