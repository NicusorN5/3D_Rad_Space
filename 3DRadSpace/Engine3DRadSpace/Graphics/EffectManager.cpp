#include "EffectManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

EffectManager::EffectManager(IGame* owner) :
	_game(owner)
{
}

void EffectManager::Add(const std::string& name, std::unique_ptr<Effect>&& effect)
{
	_effects[name] = std::move(effect);
}

Effect* EffectManager::operator[](const std::string& name)
{
	auto effect = _effects.find(name);
	if(effect != _effects.end())
	{
		return effect->second.get();
	}
	return nullptr;
}