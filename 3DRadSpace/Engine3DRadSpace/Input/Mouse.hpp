/// ------------------------------------------------------------------------------------------------
/// File:   Input/Mouse.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../Math/Point.hpp"
#include "ButtonState.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		class DLLEXPORT Mouse
		{
			ButtonState _leftButton;
			ButtonState _middleButton;
			ButtonState _rightButton;

			Math::Point _position;

			float _scrollWheel;
		public:
			Mouse();

			ButtonState LeftButton() const noexcept;
			ButtonState MiddleButton() const noexcept;
			ButtonState RightButton() const noexcept;

			Math::Point Position() const noexcept;

			float ScrollWheel() const noexcept;

			friend class Window;
		};
	}
}