#include "IObject.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

IObject::IObject(const std::string &name, bool enabled, bool visible) :
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

IObject::~IObject()
{
}