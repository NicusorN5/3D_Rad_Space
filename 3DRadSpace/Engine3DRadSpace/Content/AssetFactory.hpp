/// ------------------------------------------------------------------------------------------------
/// File:   Content/AssetFactory.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "IAsset.hpp"

namespace Engine3DRadSpace
{
	class Game;
}

namespace Engine3DRadSpace::Content
{
	class AssetFactory
	{
	private:
		GraphicsDevice* _device;
		Audio::AudioEngine* _audio;
		Physics::PhysicsEngine* _physics;
	public:
		AssetFactory(Game* game);

		AssetFactory(const AssetFactory&) = delete;
		AssetFactory(AssetFactory&&);

		AssetFactory& operator=(const AssetFactory&) = delete;
		AssetFactory& operator=(AssetFactory&&);

		template<AssetType T, typename ...Args>
		std::unique_ptr<T> Create(const std::filesystem::path& path, Args&& ...args)
		{
			using namespace Engine3DRadSpace::Audio;
			using namespace Engine3DRadSpace::Graphics;
			using namespace Engine3DRadSpace::Physics;

			//can be constructed from a GraphicsDevice
			if constexpr (ConstructibleFromGraphicsDevice<T>)
			{
				return std::make_unique<T>(_device, path, std::forward<Args>(args)...);
			}

			//can be constructed from a AudioEngine
			else if constexpr (ConstructibleFromAudioEngine<T>)
			{
				return std::make_unique<T>(_audio, path, std::forward<Args>(args)...);
			}

			//can be constructed from a PhysicsEngine
			else if constexpr (ConstructibleFromPhysicsEngine<T>)
			{
				return std::make_unique<T>(_physics, path, std::forward<Args>(args)...);
			}

			//We don't consider assets that need to be constructed from multiple abstraction layers (either GraphicsDevice, AudioEngine, PhysicsEngine, et cetera...)
		}



		GraphicsDevice* Device() const noexcept;
		Audio::AudioEngine* Audio() const noexcept;
		Physics::PhysicsEngine* Physics() const noexcept;
	};
}