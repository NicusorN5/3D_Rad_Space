#include "Rectangle.hpp"

using namespace Engine3DRadSpace::Math;

Point Rectangle::TopLeft() const
{
    return Point(X, Y);
}

Point Rectangle::TopRight() const
{
    return Point(X + Width, Y);
}


Point Rectangle::BottomLeft() const
{
    return Point(X, Y + Height);
}

Point Rectangle::BottomRight() const
{
    return Point(X + Width, Y + Height);
}

Point Rectangle::Center() const
{
    return Point((X + Width) / 2, (Y + Height) / 2);
}

int Rectangle::Area() const noexcept
{
    return Width * Height;
}


// ------------------------------------------------------------------------------ //

Vector2 RectangleF::TopLeft() const
{
    return Vector2(X, Y);
}

Vector2 RectangleF::TopRight() const
{
    return Vector2(X + Width, Y);
}


Vector2 RectangleF::BottomLeft() const
{
    return Vector2(X, Y + Height);
}

Vector2 RectangleF::BottomRight() const
{
    return Vector2(X + Width, Y + Height);
}

Vector2 RectangleF::Center() const
{
    return Vector2((X + Width) / 2.0f, (Y + Height) / 2.0f);
}

float RectangleF::Area() const noexcept
{
    return Width * Height;
}
