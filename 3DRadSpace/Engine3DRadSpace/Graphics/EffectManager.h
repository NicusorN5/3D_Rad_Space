#pragma once
#include "../Core/IService.h"
#include "../Core/IGame.h"
#include "Effect.h"
#include "IShader.h"

typedef void* E3DRSP_EffectManager;

#ifdef __cplusplus
extern "C" 
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_EffectManager E3DRSP_EffectManager_Create();
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IShader E3DRSP_EffectManager_AddShader(E3DRSP_EffectManager manager, const char* name, E3DRSP_IShader shader_moveable);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IShader E3DRSP_EffectManager_AddEffect(E3DRSP_EffectManager manager, const char* name, E3DRSP_Effect effect_moveable);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_Effect GetEffect(E3DRSP_EffectManager manager, const char* name);
	E3DRSP_GRAPHICS_EXPORT E3DRSP_IShader GetShader(E3DRSP_EffectManager manager, const char* name);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_EffectManager_Destroy(E3DRSP_EffectManager manager);
#ifdef __cplusplus
}
#endif