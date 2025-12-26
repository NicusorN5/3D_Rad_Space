#pragma once
#include "../Core/IService.hpp"
#include "Effect.hpp"
#include "IShader.hpp"

namespace Engine3DRadSpace
{
	class IGame;
}

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT EffectManager : public IService
	{
		IGame* _game;

		std::unordered_map<std::string, std::unique_ptr<Effect>> _effects;
		std::unordered_map<std::string, std::unique_ptr<IShader>> _shaders;
	public:
		EffectManager();

		EffectManager(const EffectManager&) = delete;
		EffectManager(EffectManager&&) = delete;

		EffectManager& operator=(const EffectManager&) = delete;
		EffectManager& operator=(EffectManager&) = delete;

		Effect* Add(const std::string& name, std::unique_ptr<Effect>&& effect);
		IShader* Add(const std::string& name, std::unique_ptr<IShader>&& shader);
		Effect* GetEffect(const std::string& name);
		IShader* GetShader(const std::string& name);

		~EffectManager() override = default;
	};
}