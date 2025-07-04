#include "ColorBox.hpp"
#include <stdexcept>
#include <CommCtrl.h>

WNDPROC ColorBox::staticProc = nullptr;

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

LRESULT WINAPI ColorBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ColorBox *cb = reinterpret_cast<ColorBox *>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
	switch (msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, cb->brush);
			EndPaint(hwnd, &ps);
			return 0;
		}
		default:
			return ColorBox::staticProc(hwnd, msg, wParam, lParam);
	}
}

ColorBox::ColorBox(HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, Color color) :
	IControl(owner, hInstance),
	customColors{ 0xFFFFFF }
{
	SetColor(color);

	window = CreateWindowExA(
		WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME,
		"Static",
		"",
		SS_NOTIFY | WS_CHILD | WS_VISIBLE,
		x,
		y,
		cx,
		cy,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	SetWindowLongPtrA(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	staticProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(ColorBoxProc)));
}

void ColorBox::SetColor()
{
	CHOOSECOLORA cc{};
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = owner;
	cc.Flags = CC_FULLOPEN | CC_ANYCOLOR;
	cc.lpCustColors = &customColors[0];
	cc.rgbResult = RGB(color.R * 255, color.G * 255, color.B * 255);

	BOOL r = ChooseColorA(&cc);
	if (r)
	{
		SetColor(Color::FromRGB(
			GetRValue(cc.rgbResult),
			GetGValue(cc.rgbResult),
			GetBValue(cc.rgbResult)
		));
	}
}

void ColorBox::SetColor(Color color)
{
	this->color = color; //store a copy of the color, to avoid using GetObject().

	if(brush) DeleteObject(brush);

#pragma warning(push)
#pragma warning(disable: 4244)
	uint8_t r(255 * color.R);
	uint8_t g(255 * color.G);
	uint8_t b(255 * color.B);
#pragma warning(pop)

	brush = CreateSolidBrush(RGB(r, g, b));
	if (brush == nullptr) throw std::bad_alloc();

	RedrawWindow(window, nullptr, nullptr, RDW_INTERNALPAINT | RDW_INVALIDATE);
}

Color ColorBox::GetColor()
{
	return color;
}

HWND ColorBox::GetWindowHandle()
{
	return window;
}

ColorBox::~ColorBox()
{
	if (brush != nullptr)
	{
		DeleteObject(brush);
		brush = nullptr;
	}
}

void ColorBox::HandleClick(HWND clickedWindow)
{
	if(clickedWindow == window)
	{
		SetColor();
	}
}
