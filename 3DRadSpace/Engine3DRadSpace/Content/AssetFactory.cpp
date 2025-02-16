/// ------------------------------------------------------------------------------------------------
/// File:   Content/AssetFactory.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "AssetFactory.hpp"
#include "../Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Physics;

AssetFactory::AssetFactory(Game* game) :
	_device(game->Device.get()),
	_physics(game->Physics.get()),
	_audio(game->Audio.get())
{
	if(!game->Audio)
	{
		game->RequestAudioInitialization();
		_audio = game->Audio.get();
	}

	if(!game->Physics)
	{
		game->RequestPhysicsInitialization({0, -9.8f, 0});
		_physics = game->Physics.get();
	}
}

AssetFactory::AssetFactory(AssetFactory&& moved) :
	_device(moved._device),
	_physics(moved._physics),
	_audio(moved._audio)
{
	moved._device = nullptr;
	moved._physics = nullptr;
	moved._audio = nullptr;
}

AssetFactory& AssetFactory::operator=(AssetFactory&& moved)
{
	if(&moved != this)
	{
		_device = moved._device;
		_physics = moved._physics;
		_audio = moved._audio;

		moved._device = nullptr;
		moved._physics = nullptr;
		moved._audio = nullptr;
	}
	return *this;
}

GraphicsDevice* AssetFactory::Device() const noexcept
{
	return this->_device;
}

Audio::AudioEngine* AssetFactory::Audio() const noexcept
{
	return this->_audio;
}

Physics::PhysicsEngine* AssetFactory::Physics() const noexcept
{
	return this->_physics;
}
