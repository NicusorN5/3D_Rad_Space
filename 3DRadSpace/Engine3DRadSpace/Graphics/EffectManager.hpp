#pragma once
#include "../Core/IService.hpp"

namespace Engine3DRadSpace
{
	class IGame;
}

namespace Engine3DRadSpace::Graphics
{
	class Effect;

	class E3DRSP_GRAPHICS_EXPORT EffectManager : public IService
	{
		IGame* _game;

		std::unordered_map<std::string, std::unique_ptr<Effect>> _effects;
	public:
		EffectManager(IGame* owner);

		EffectManager(const EffectManager&) = delete;
		EffectManager(EffectManager&&) = delete;

		EffectManager& operator=(const EffectManager&) = delete;
		EffectManager& operator=(EffectManager&) = delete;

		void Add(const std::string& name, std::unique_ptr<Effect>&& effect);
		Effect* operator[](const std::string& name);

		~EffectManager() override = default;
	};
}