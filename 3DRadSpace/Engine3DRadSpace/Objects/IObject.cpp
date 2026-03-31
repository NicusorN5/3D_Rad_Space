#include "IObject.hpp"
#include "IObject.h"
#include "ObjectList.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

IObject::IObject(const std::string &name, bool enabled, bool visible) :
	_parent(nullptr),
	Name(name),
	Enabled(enabled),
	Visible(visible)
{
}

void IObject::InternalInitialize(IGame* game)
{
	_game = game;
	_device = game->GetService<IGraphicsDevice>({});
}

IGraphicsDevice* IObject::GetGraphicsDeviceHandle() const noexcept
{
	return _device;
}

IGame* IObject::GetGame() const noexcept
{
	return _game;
}

void IObject::Enable()
{
	Enabled = true;
}

void IObject::Disable()
{
	Enabled = false;
}

bool IObject::Switch()
{
	Enabled = !Enabled;
	return Enabled;
}

void IObject::Show()
{
	Visible = true;
}

void IObject::Hide()
{
	Visible = false;
}

bool IObject::SwitchVisibility()
{
	Visible = !Visible;
	return Visible;
}

IObject* IObject::operator[](size_t idxChild) const
{
	return Children[idxChild];
}

IObject* IObject::GetParent() const noexcept
{
	return _parent;
}

void IObject::SetParent(IObject* currentOwner, IObject* newParent) noexcept
{
	if(_parent == nullptr)
	{
		_parent = newParent;
		return;
	}

	if(currentOwner == this->_parent)
	{
		this->_parent = newParent;
		currentOwner->_parent = nullptr;
		return;
	}
}

bool IObject::HasParent() const noexcept
{
	return _parent != nullptr;
}

IObject::~IObject()
{
}

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