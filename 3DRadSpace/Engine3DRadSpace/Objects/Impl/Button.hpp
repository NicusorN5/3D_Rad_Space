#pragma once
#include "Sprite.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a clickable sprite, that has different UV coordinates for button states.
	/// </summary>
	/// <remarks>
	/// 
	/// </remarks>
	class E3DRSP_OBJECTS_IMPL_EXPORT Button : public Sprite
	{
	public:
		Button();

		Math::RectangleF IdleTextureRect;
		Math::Color IdleClickColor;

		Math::RectangleF HoverTextureRect;
		Math::Color HoverTintColor;

		Math::RectangleF ClickTextureRect;
		Math::Color ClickTintColor;

		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;

		~Button() override = default;
	};
}