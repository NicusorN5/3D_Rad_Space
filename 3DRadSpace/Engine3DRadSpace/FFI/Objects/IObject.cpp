#include "../../Objects/IObject.hpp"
#include "IObject.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

E3DRSP_UUID E3DRSP_IObject_GetUUID(E3DRSP_IObject object)
{
	auto uuid = static_cast<IObject*>(object)->GetUUID();
	E3DRSP_UUID c_uuid;
	memcpy_s(&c_uuid, sizeof(E3DRSP_UUID), &uuid, sizeof(Reflection::UUID));
	return c_uuid;
}

E3DRSP_IGizmo E3DRSP_IObject_GetGizmo(E3DRSP_IObject object)
{
	auto gizmo = static_cast<IObject*>(object)->GetGizmo();
	return static_cast<E3DRSP_IGizmo>(gizmo);
}

E3DRSP_IGraphicsDevice E3DRSP_IObject_GetGraphicsDeviceHandle(E3DRSP_IObject object)
{
	auto device = static_cast<IObject*>(object)->GetGraphicsDeviceHandle();
	return static_cast<E3DRSP_IGraphicsDevice>(device);
}

E3DRSP_IGame E3DRSP_IObject_GetGame(E3DRSP_IObject object)
{
	auto game = static_cast<IObject*>(object)->GetGame();
	return static_cast<E3DRSP_IGame>(game);
}

void E3DRSP_IObject_Enable(E3DRSP_IObject object)
{
	static_cast<IObject*>(object)->Enable();
}

void E3DRSP_IObject_Disable(E3DRSP_IObject object)
{
	static_cast<IObject*>(object)->Disable();
}

bool E3DRSP_IObject_Switch(E3DRSP_IObject object)
{
	return static_cast<IObject*>(object)->Switch();
}

bool E3DRSP_IObject_IsEnabled(E3DRSP_IObject object)
{
	return static_cast<IObject*>(object)->Enabled;
}

void E3DRSP_IObject_Show(E3DRSP_IObject object)
{
	static_cast<IObject*>(object)->Show();
}

void E3DRSP_IObject_Hide(E3DRSP_IObject object)
{
	static_cast<IObject*>(object)->Hide();
}

bool E3DRSP_IObject_SwitchVisibility(E3DRSP_IObject object)
{
	return static_cast<IObject*>(object)->SwitchVisibility();
}

bool E3DRSP_IObject_IsVisible(E3DRSP_IObject object)
{
	return static_cast<IObject*>(object)->Visible;
}

const char* E3DRSP_IObject_GetName(E3DRSP_IObject object)
{
	return static_cast<IObject*>(object)->Name.c_str();
}

void E3DRSP_IObject_SetName(E3DRSP_IObject object, const char* name)
{
	static_cast<IObject*>(object)->Name = std::string(name);
}

void* E3DRSP_IObject_Children(E3DRSP_IObject object)
{
	return static_cast<void*>(&static_cast<IObject*>(object)->Children);
}

E3DRSP_IObject E3DRSP_IObject_GetChild(E3DRSP_IObject object, size_t idxChild)
{
	return static_cast<E3DRSP_IObject>(static_cast<IObject*>(object)->operator[](idxChild));
}

size_t E3DRSP_IObject_GetChildrenCount(E3DRSP_IObject object)
{
	return static_cast<IObject*>(object)->GetChildrenCount();
}

E3DRSP_IObject E3DRSP_IObject_GetParent(E3DRSP_IObject object)
{
	return static_cast<E3DRSP_IObject>(static_cast<IObject*>(object)->GetParent());
}

void E3DRSP_IObject_SetParent(E3DRSP_IObject object, E3DRSP_IObject currentOwner, E3DRSP_IObject newParent)
{
	static_cast<IObject*>(object)->SetParent(static_cast<IObject*>(currentOwner), static_cast<IObject*>(newParent));
}