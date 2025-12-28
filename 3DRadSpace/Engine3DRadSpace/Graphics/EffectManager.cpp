#include "EffectManager.hpp"
#include "EffectManager.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

EffectManager::EffectManager() :
	_game(nullptr)
{
}

Effect* EffectManager::Add(const std::string& name, std::unique_ptr<Effect>&& effect)
{
	_effects[name] = std::move(effect);
	return _effects[name].get();
}

IShader* EffectManager::Add(const std::string& name, std::unique_ptr<IShader>&& shader)
{
	_shaders[name] = std::move(shader);
	return _shaders[name].get();
}

Effect* EffectManager::GetEffect(const std::string& name)
{
	auto effect = _effects.find(name);
	if(effect != _effects.end())
	{
		return effect->second.get();
	}
	return nullptr;
}

IShader* EffectManager::GetShader(const std::string& name)
{
	auto shader = _shaders.find(name);
	if (shader != _shaders.end())
	{
		return shader->second.get();
	}
	return nullptr;
}

E3DRSP_EffectManager E3DRSP_EffectManager_Create()
{
	return new EffectManager();
}

E3DRSP_IShader E3DRSP_EffectManager_AddShader(E3DRSP_EffectManager manager, const char* name, E3DRSP_IShader shader_moveable)
{
	return static_cast<EffectManager*>(manager)->Add(
		std::string(name),
		std::unique_ptr<IShader>(reinterpret_cast<IShader*>(shader_moveable))
	);
}

E3DRSP_IShader E3DRSP_EffectManager_AddEffect(E3DRSP_EffectManager manager, const char* name, E3DRSP_Effect effect_moveable)
{
	return static_cast<EffectManager*>(manager)->Add(
		std::string(name), 
		std::unique_ptr<Effect>(reinterpret_cast<Effect*>(effect_moveable))
	);
}

E3DRSP_Effect GetEffect(E3DRSP_EffectManager manager, const char* name)
{
	return static_cast<EffectManager*>(manager)->GetEffect(name);
}

E3DRSP_IShader GetShader(E3DRSP_EffectManager manager, const char* name)
{
	return static_cast<EffectManager*>(manager)->GetShader(name);
}

void E3DRSP_EffectManager_Destroy(E3DRSP_EffectManager manager)
{
	delete static_cast<EffectManager*>(manager);
}