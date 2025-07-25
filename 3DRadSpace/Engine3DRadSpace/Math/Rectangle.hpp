#pragma once
#include "Point.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		struct E3DRSP_MATH_EXPORT Rectangle
		{
			explicit constexpr Rectangle(int x = 0, int y = 0, int w = 0, int h = 0) :
				X(x),
				Y(y),
				Width(w),
				Height(h)
			{
			}
			explicit Rectangle(Point min, Point max) :
				X(min.X),
				Y(min.Y),
				Width(max.X - min.X),
				Height(max.Y - min.Y)
			{
			}

			int X;
			int Y;
			int Width;
			int Height;

			Point TopLeft() const;
			Point TopRight() const;
			Point BottomLeft() const;
			Point BottomRight() const;
			Point Center() const;

			int Area() const noexcept;

			bool operator ==(const Rectangle& r) const = default;
			bool operator !=(const Rectangle& r) const = default;
		};

		struct E3DRSP_MATH_EXPORT RectangleF
		{
			explicit constexpr RectangleF(float x = 0, float y = 0, float w = 0, float h = 0) :
				X(x),
				Y(y),
				Width(w),
				Height(h)
			{
			}
			explicit RectangleF(Vector2 min, Vector2 max) :
				X(min.X),
				Y(min.Y),
				Width(max.X - min.X),
				Height(max.Y - min.Y)
			{
			}

			float X;
			float Y;
			float Width;
			float Height;

			Vector2 TopLeft() const;
			Vector2 TopRight() const;
			Vector2 BottomLeft() const;
			Vector2 BottomRight() const;
			Vector2 Center() const;

			float Area() const noexcept;

			bool operator ==(const RectangleF& r) const = default;
			bool operator !=(const RectangleF& r) const = default;
		};
	}
}

