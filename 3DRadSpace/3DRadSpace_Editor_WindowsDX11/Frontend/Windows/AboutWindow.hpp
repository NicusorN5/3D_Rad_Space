#pragma once
#include "../Controls/Dialog.hpp"

class AboutWindow : public Dialog
{
	HWND _label = nullptr;
	HWND _iconPictureBox = nullptr;
	HWND _okButton = nullptr;
	
	void _createControls();
public:
	AboutWindow(HWND owner, HINSTANCE hInstance);

	void ShowDialog();

	friend INT_PTR WINAPI AboutWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};