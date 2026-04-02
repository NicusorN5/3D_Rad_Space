#pragma once
#include "../Math/Point.h"
#include "../Input/Mouse.h"
#include "../Input/Keyboard.h"
#include "../Math/Rectangle.h"

typedef void* E3DRSP_Window;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_Window E3DRSP_NATIVE_EXPORT E3DRSP_Window_Create(const char* title, size_t width, size_t height);

	E3DRSP_NATIVE_EXPORT void* E3DRSP_Window_NativeHandle(E3DRSP_Window window);

	/// <summary>
	/// 
	/// </summary>
	void E3DRSP_NATIVE_EXPORT E3DRSP_Window_ProcessMessages(E3DRSP_Window window);

	E3DRSP_Mouse E3DRSP_NATIVE_EXPORT E3DRSP_Window_GetMouseState(E3DRSP_Window window);
	E3DRSP_Keyboard E3DRSP_NATIVE_EXPORT E3DRSP_Window_GetKeyboardState(E3DRSP_Window window);

	E3DRSP_Point E3DRSP_NATIVE_EXPORT E3DRSP_Window_Size(E3DRSP_Window window);
	E3DRSP_RectangleF E3DRSP_NATIVE_EXPORT E3DRSP_Window_RectangleF(E3DRSP_Window window);
	E3DRSP_Rectangle E3DRSP_NATIVE_EXPORT E3DRSP_Window_Rectangle(E3DRSP_Window window);
	bool E3DRSP_NATIVE_EXPORT E3DRSP_Window_IsFocused(E3DRSP_Window window);
	void E3DRSP_NATIVE_EXPORT E3DRSP_Window_SetMousePosition(E3DRSP_Window window, const E3DRSP_Point* p);
	void E3DRSP_NATIVE_EXPORT E3DRSP_Window_SetTitle(E3DRSP_Window window, const char* title);
	void E3DRSP_NATIVE_EXPORT E3DRSP_Window_Destroy(E3DRSP_Window window);
#ifdef __cplusplus
}
#endif