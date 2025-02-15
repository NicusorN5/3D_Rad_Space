/// ------------------------------------------------------------------------------------------------
/// File:   IObject.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "IObject.hpp"
#include "Game.hpp"

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

GraphicsDevice* IObject::GetGraphicsDeviceHandle()
{
	return _device;
}

Game* IObject::GetGame()
{
	return _game;
}
