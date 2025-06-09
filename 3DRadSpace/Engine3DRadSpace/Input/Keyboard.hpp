#pragma once
#include "../Core/Libs.hpp"
#include "Key.hpp"
#include "KeyState.hpp"

namespace Engine3DRadSpace
{
	namespace Native
	{
		class Window;
	}

	namespace Input
	{
		class E3DRSP_INPUT_EXPORT Keyboard
		{
			uint8_t _keys[10];

			/// used inside the Window class
			void _addKey(uint8_t k);
			void _removeKey(uint8_t k);
			void _erase();
		public:
			Keyboard();

			bool IsKeyDown(Key k) const noexcept;
			bool IsKeyUp(Key k) const noexcept;
			bool IsAnyKeyDown() const noexcept;

			KeyState operator[](const Key k);

			friend class Native::Window;
		};
	}
}