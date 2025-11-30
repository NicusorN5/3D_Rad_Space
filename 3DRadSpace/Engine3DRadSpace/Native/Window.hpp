#pragma once
#include "../Graphics/IGraphicsDevice.hpp"
#include "../Input/Mouse.hpp"
#include "../Input/Keyboard.hpp"

namespace Engine3DRadSpace::Native
{
	class E3DRSP_NATIVE_EXPORT Window
	{
		void* _window;

#ifdef _WIN32
		HINSTANCE _hInstance;
#endif

		Input::Mouse _mouse;
		Input::Keyboard _keyboard;

		void _keyUp(uint8_t k);
		void _keyDown(uint8_t k);
		void _scrollwheel(float dw);
		void _handleMouse(Math::Point pos,bool left,bool middle, bool right);
		void _resetKeyboard();
	public:
		Window(const std::string& title, size_t width = 800, size_t height = 600);
		//Used for the Windows editor frontend.
		Window(void* hInstance, void* parentWindow);

		Window(Window &) = delete;
		Window(Window &&wnd) noexcept;

		Window& operator=(Window& wnd) = delete;
		Window &operator=(Window &&wnd) noexcept;

		void* NativeHandle() const noexcept;

		/// <summary>
		/// 
		/// </summary>
		void ProcessMessages();

		Input::Mouse& GetMouseState();
		Input::Keyboard& GetKeyboardState();

		Math::Point Size() const noexcept;
		Math::RectangleF RectangleF() const noexcept;
		Math::Rectangle Rectangle() const noexcept;
		bool IsFocused() const noexcept;
		
		void SetMousePosition(const Math::Point& p);

		/// <summary>
		/// Sets the window title.
		/// </summary>
		/// <param name="title">Title string.</param>
		void SetTitle(const std::string& title);

		~Window();

#ifdef _WIN32
		friend LRESULT E3DRSP_NATIVE_EXPORT CALLBACK GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
	};
}

