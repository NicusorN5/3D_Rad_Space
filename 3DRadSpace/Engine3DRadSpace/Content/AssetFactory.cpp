#include "AssetFactory.hpp"
#include "../Games/Game.hpp"
#include "Assets.hpp"
using namespace Engine3DRadSpace::Internal;

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
		//game->RequestAudioInitialization();
		_audio = game->Audio.get();
	}

	if(!game->Physics)
	{
		//game->RequestPhysicsInitialization({0, -9.8f, 0});
		_physics = game->Physics.get();
	}
}

AssetFactory::AssetFactory(AssetFactory&& moved) noexcept :
	_device(moved._device),
	_physics(moved._physics),
	_audio(moved._audio)
{
	moved._device = nullptr;
	moved._physics = nullptr;
	moved._audio = nullptr;
}

AssetFactory& AssetFactory::operator=(AssetFactory&& moved) noexcept
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

IAsset* AssetFactory::CreateAssetInstance(const Reflection::UUID &nuuid ,const std::filesystem::path& path)
{
	Engine3DRadSpace::Internal::RegisterDefaultAssets();
	if (this == nullptr) return nullptr;
	
	for (auto& [uuid, ctor] : Internal::asset_types)
	{
		if(uuid == nuuid)
		{
			switch(ctor.index())
			{
				case 0:
					return std::get<AssetCtor1>(ctor)(_device, path);
				case 1:
					return std::get<AssetCtor2>(ctor)(_physics, path);
				case 2:
					return std::get<AssetCtor3>(ctor)(_audio, path);
				case 3:
					return std::get<AssetCtor4>(ctor)(path);
				default:
					std::unreachable();
			}
		}
	}
	return nullptr;
}