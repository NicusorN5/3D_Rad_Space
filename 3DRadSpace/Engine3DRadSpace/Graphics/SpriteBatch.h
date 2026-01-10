#pragma once
#include "ITexture2D.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "IDepthStencilBuffer.h"
#include "IRasterizerState.h"
#include "IBlendState.h"
#include "FlipMode.h"
#include "Font.h"
#include "Effect.h"
#include "../Math/Point.h"
#include "../Math/Vector2.h"

typedef void* E3DRSP_IGraphicsDevice;
struct E3DRSP_RectangleF;
typedef void* E3DRSP_SpriteBatch;

enum E3DRSP_SpriteBatchSortMode
{
	/// <summary>
	/// Do not sort the sprites.
	/// </summary>
	E3DRSP_SpriteBatchSortMode_Immediate,
	/// <summary>
	/// Sort by texture. Use this if you want to optimize the number of draw calls.
	/// </summary>
	E3DRSP_SpriteBatchSortMode_SortedByTexture,
	/// <summary>
	/// Sort by depth. From front (0.0f) to back (-inf).
	/// </summary>
	E3DRSP_SpriteBatchSortMode_SortedByDepth_FrontToBack,
	/// <summary>
	/// Sort by depth. From back (-inf) to front (0.0f).
	/// </summary>
	E3DRSP_SpriteBatchSortMode_SortedByDepth_BackToFront,
};

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_GRAPHICS_EXPORT E3DRSP_SpriteBatch E3DRSP_SpriteBatch_Create(E3DRSP_IGraphicsDevice device);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_Begin(E3DRSP_SpriteBatch spriteBatch, E3DRSP_SpriteBatchSortMode sortingMode);
	//E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_Begin2(E3DRSP_SpriteBatch spriteBatch, E3DRSP_SpriteBatchSortMode sortingMode, E3DRSP_ISamplerState *samplerState_moveable);
		
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_DrawNormalized(
		E3DRSP_SpriteBatch spriteBatch,
		E3DRSP_ITexture2D texture,
		const E3DRSP_RectangleF* coords,
		const E3DRSP_RectangleF* source,
		const E3DRSP_Color* tintColor,
		float rotation, 
		E3DRSP_FlipMode flipMode,
		float depth
	);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_DrawNormalized2(
		E3DRSP_SpriteBatch spriteBatch,
		E3DRSP_ITexture2D texture,
		const E3DRSP_RectangleF* coords,
		const E3DRSP_Rectangle* source,
		const E3DRSP_Color* tintColor,
		float rotation,
		E3DRSP_FlipMode flipMode,
		float depth
	);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_Draw(
		E3DRSP_SpriteBatch spriteBatch,
		E3DRSP_ITexture2D texture,
		const E3DRSP_Rectangle* coords,
		const E3DRSP_Rectangle* source,
		const E3DRSP_Color* tintColor,
		float rotation,
		E3DRSP_FlipMode flipMode,
		float depth
	);
	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_Draw2(
		E3DRSP_SpriteBatch spriteBatch,
		E3DRSP_ITexture2D texture,
		const E3DRSP_Rectangle* coords,
		const E3DRSP_Color* tintColor,
		float rotation,
		E3DRSP_FlipMode flipMode,
		float depth
	);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_DrawString(
		E3DRSP_SpriteBatch spriteBatch,
		E3DRSP_Font font,
		const char* text, 
		const E3DRSP_Vector2* pos,
		float size,
		const E3DRSP_Color* tintColor,
		float rotation,
		E3DRSP_FlipMode flipMode,
		float depth
	);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_DrawString2(
		E3DRSP_SpriteBatch spriteBatch,
		E3DRSP_Font font,
		const char* text,
		const E3DRSP_Point* pos, 
		float size, 
		const E3DRSP_Color* tintColor,
		float rotation,
		E3DRSP_FlipMode flipMode,
		float depth
	);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_End(E3DRSP_SpriteBatch spriteBatch);

	E3DRSP_GRAPHICS_EXPORT void E3DRSP_SpriteBatch_Destroy(E3DRSP_SpriteBatch spriteBatch);
#ifdef __cplusplus
}
#endif