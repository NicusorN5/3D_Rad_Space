#include "EffectManager.h"
#include "../../Graphics/EffectManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

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

E3DRSP_Effect E3DRSP_EffectManager_AddEffect(E3DRSP_EffectManager manager, const char* name, E3DRSP_Effect effect_moveable)
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