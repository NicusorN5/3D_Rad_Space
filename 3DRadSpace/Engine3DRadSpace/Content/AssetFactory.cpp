/// ------------------------------------------------------------------------------------------------
/// File:   Content/AssetFactory.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "AssetFactory.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Physics;

AssetFactory::AssetFactory(Game* game) :
	_device(game->Device.get()),
	_physics(game->Physics.get()),
	_audio(nullptr)
{
}
