#include "Mouse.hpp"

using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

Mouse::Mouse() :
	_leftButton(ButtonState::Released),
	_middleButton(ButtonState::Released),
	_rightButton(ButtonState::Released),
	_position(),
	_scrollWheel(0)
{
};

ButtonState Mouse::LeftButton() const noexcept
{
    return _leftButton;
}

ButtonState Mouse::MiddleButton() const noexcept
{
    return _middleButton;
}

ButtonState Mouse::RightButton() const noexcept
{
    return _rightButton;
}

Point Mouse::Position() const noexcept
{
    return _position;
}

float Mouse::ScrollWheel() const noexcept
{
    return _scrollWheel;
}
