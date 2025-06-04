#include "IObject.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

IObject::IObject(const std::string &name, bool enabled, bool visible) :
	Name(name),
	Enabled(enabled),
	Visible(visible)
{
}

void Engine3DRadSpace::IObject::InternalInitialize(Game* game)
{
	_game = game;
	_device = game->Device.get();
}

Graphics::GraphicsDevice* IObject::GetGraphicsDeviceHandle()
{
	return _device;
}

Game* IObject::GetGame()
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

IObject::~IObject()
{
	//auto gizmo = GetGizmo();
}