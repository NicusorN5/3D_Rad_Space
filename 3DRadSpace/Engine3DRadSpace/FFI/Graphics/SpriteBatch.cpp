#include "SpriteBatch.h"
#include "../../Graphics/SpriteBatch.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_SpriteBatch E3DRSP_SpriteBatch_Create(E3DRSP_IGraphicsDevice device)
{
	return new SpriteBatch(reinterpret_cast<IGraphicsDevice*>(device));
}

void E3DRSP_SpriteBatch_Begin(E3DRSP_SpriteBatch spriteBatch, E3DRSP_SpriteBatchSortMode sortingMode)
{
	static_cast<SpriteBatch*>(spriteBatch)->Begin(static_cast<SpriteBatchSortMode>(sortingMode));
}

//void E3DRSP_SpriteBatch_Begin2(E3DRSP_SpriteBatch spriteBatch, E3DRSP_SpriteBatchSortMode sortingMode, E3DRSP_ISamplerState* samplerState_moveable)
//{
//	static_cast<SpriteBatch*>(spriteBatch)->Begin(
//		static_cast<SpriteBatchSortMode>(sortingMode), 
//		std::make_unique<ISamplerState>(reinterpret_cast<ISamplerState*>(samplerState_moveable))
//	);
//}

void E3DRSP_SpriteBatch_DrawNormalized(
	E3DRSP_SpriteBatch spriteBatch,
	E3DRSP_ITexture2D texture,
	const E3DRSP_RectangleF* coords,
	const E3DRSP_RectangleF* source,
	const E3DRSP_Color* tintColor,
	float rotation,
	E3DRSP_FlipMode flipMode,
	float depth
)
{
	static_cast<SpriteBatch*>(spriteBatch)->DrawNormalized(
		reinterpret_cast<ITexture2D*>(texture),
		std::bit_cast<const Math::RectangleF>(*coords),
		std::bit_cast<const Math::Rectangle>(*source),
		std::bit_cast<const Color>(*tintColor),
		rotation,
		static_cast<FlipMode>(flipMode),
		depth
	);
}

void E3DRSP_SpriteBatch_DrawNormalized2(
	E3DRSP_SpriteBatch spriteBatch,
	E3DRSP_ITexture2D texture,
	const E3DRSP_RectangleF* coords,
	const E3DRSP_Rectangle* source,
	const E3DRSP_Color* tintColor,
	float rotation,
	E3DRSP_FlipMode flipMode,
	float depth
)
{
	static_cast<SpriteBatch*>(spriteBatch)->DrawNormalized(
		reinterpret_cast<ITexture2D*>(texture),
		std::bit_cast<const Math::RectangleF>(*coords),
		std::bit_cast<const Math::Rectangle>(*source),
		std::bit_cast<const Color>(*tintColor),
		rotation,
		static_cast<FlipMode>(flipMode),
		depth
	);
}

void E3DRSP_SpriteBatch_Draw(
	E3DRSP_SpriteBatch spriteBatch,
	E3DRSP_ITexture2D texture,
	const E3DRSP_Rectangle* coords,
	const E3DRSP_Rectangle* source,
	const E3DRSP_Color* tintColor,
	float rotation,
	E3DRSP_FlipMode flipMode,
	float depth
)
{
	static_cast<SpriteBatch*>(spriteBatch)->Draw(
		reinterpret_cast<ITexture2D*>(texture),
		std::bit_cast<const Math::Rectangle>(*coords),
		std::bit_cast<const Math::Rectangle>(*source),
		std::bit_cast<const Color>(*tintColor),
		rotation,
		static_cast<FlipMode>(flipMode),
		depth
	);
}

void E3DRSP_SpriteBatch_Draw2(
	E3DRSP_SpriteBatch spriteBatch,
	E3DRSP_ITexture2D texture,
	const E3DRSP_Rectangle* coords,
	const E3DRSP_Color* tintColor,
	float rotation,
	E3DRSP_FlipMode flipMode,
	float depth
)
{
	static_cast<SpriteBatch*>(spriteBatch)->Draw(
		reinterpret_cast<ITexture2D*>(texture),
		std::bit_cast<const Math::Rectangle>(*coords),
		std::bit_cast<const Color>(*tintColor),
		rotation,
		static_cast<FlipMode>(flipMode),
		depth
	);
}

void E3DRSP_SpriteBatch_DrawString(
	E3DRSP_SpriteBatch spriteBatch,
	E3DRSP_Font font,
	const char* text,
	const E3DRSP_Vector2* pos,
	float size,
	const E3DRSP_Color* tintColor,
	float rotation,
	E3DRSP_FlipMode flipMode,
	float depth
)
{
	reinterpret_cast<SpriteBatch*>(spriteBatch)->DrawString(
		reinterpret_cast<Font*>(font),
		text,
		std::bit_cast<const Vector2>(*pos),
		size,
		std::bit_cast<const Color>(*tintColor),
		rotation,
		static_cast<FlipMode>(flipMode),
		depth
	);
}

void E3DRSP_SpriteBatch_DrawString2(
	E3DRSP_SpriteBatch spriteBatch,
	E3DRSP_Font font,
	const char* text,
	const E3DRSP_Point* pos,
	float size,
	const E3DRSP_Color* tintColor,
	float rotation,
	E3DRSP_FlipMode flipMode,
	float depth
)
{
	reinterpret_cast<SpriteBatch*>(spriteBatch)->DrawString(
		static_cast<Font*>(font),
		text,
		std::bit_cast<const Math::Point>(*pos),
		size,
		std::bit_cast<const Color>(*tintColor),
		rotation,
		static_cast<FlipMode>(flipMode),
		depth
	);
}

void E3DRSP_SpriteBatch_End(E3DRSP_SpriteBatch spriteBatch)
{
	static_cast<SpriteBatch*>(spriteBatch)->End();
}

void E3DRSP_SpriteBatch_Destroy(E3DRSP_SpriteBatch spriteBatch)
{
	delete static_cast<SpriteBatch*>(spriteBatch);
}