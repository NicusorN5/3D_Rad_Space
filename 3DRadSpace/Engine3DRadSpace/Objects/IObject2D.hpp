#pragma once
#include "IObject.hpp"
#include "IDrawable2D.hpp"
#include "../Math/Vector2.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_OBJECTS_EXPORT IObject2D : public IObject, public IDrawable2D
	{
	protected:
		explicit IObject2D(
			const std::string& name = "",
			bool enabled = false,
			bool visible = false,
			const Math::Vector2& pos = Math::Vector2::Zero(),
			const Math::Vector2& scale = Math::Vector2(0.1f, 0.1f),
			float rotation = 0.0f,
			const Math::Vector2& pivot = Math::Vector2::Zero(),
			float depth = 0.0f
		);
	public:

		Math::Vector2 Position;
		Math::Vector2 RotationCenter;
		Math::Vector2 Scale;
		float Depth;
		float Rotation;

		virtual ~IObject2D() = default;
	};
}