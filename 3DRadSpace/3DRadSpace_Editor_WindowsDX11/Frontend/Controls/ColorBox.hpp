#pragma once
#include "IControl.hpp"
#include <Engine3DRadSpace\Math\Color.hpp>
#include <array>

class ColorBox : public IControl
{
	Engine3DRadSpace::Math::Color color;
	HBRUSH brush;
	static WNDPROC staticProc;
	std::array<COLORREF,16> customColors;
public:
	ColorBox(
		HWND owner,
		HINSTANCE hInstance,
		int x,
		int y, 
		int cx,
		int cy,
		Engine3DRadSpace::Math::Color color
	);

	/// <summary>
	/// Opens the color dialog box.
	/// </summary>
	void SetColor();
	/// <summary>
	/// Sets a defined color.
	/// </summary>
	/// <param name="color">Color. Only R, G, B components are used.</param>
	void SetColor(Engine3DRadSpace::Math::Color color);
	Engine3DRadSpace::Math::Color GetColor();

	HWND GetWindowHandle();
	virtual void HandleClick(HWND clickedWindow) override;

	~ColorBox();

	friend LRESULT WINAPI ColorBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

