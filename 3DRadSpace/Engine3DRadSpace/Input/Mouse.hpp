#pragma once
#include "../Math/Point.hpp"
#include "ButtonState.hpp"

namespace Engine3DRadSpace
{
	namespace Native
	{
		class Window;
	}

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

			friend class Native::Window;
		};
	}
}