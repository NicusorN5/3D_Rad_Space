#include "Dialog.hpp"

Dialog::Dialog(HWND hwndOwner, HINSTANCE instance, DLGPROC dlgproc, const std::string &windowTitle, short sx, short sy):
	hInstance(instance),
	dialogProc(dlgproc),
	owner(hwndOwner),
	window(nullptr)
	//Allocate memory for the dialog box
{
	int numWChars = MultiByteToWideChar(CP_ACP, 0, windowTitle.c_str(), -1, nullptr, 0);

	hGlobal = GlobalAlloc(GMEM_ZEROINIT, sizeof(DLGTEMPLATE) + (numWChars * sizeof(wchar_t)) + (4 * sizeof(WORD)));
	if (hGlobal == nullptr) throw std::bad_alloc();

	//Fill the dialog template data.
	dialogTemplate = static_cast<LPDLGTEMPLATE>(GlobalLock(hGlobal));
	if (dialogTemplate == nullptr) throw std::bad_alloc();

	//dialogTemplate->style = WS_POPUP | WS_CAPTION | WS_THICKFRAME | DS_MODALFRAME | WS_SYSMENU | DS_CENTER;
	dialogTemplate->style = WS_POPUP | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME | DS_CENTER;
	dialogTemplate->dwExtendedStyle = 0;
	dialogTemplate->cdit = 0;

	dialogTemplate->x = 0;
	dialogTemplate->y = 0;

	dialogTemplate->cx = sx;
	dialogTemplate->cy = sy;

	//After the dialog template, more data is expected, a menu handle, a dialog box class, title, and then dialog controls, such as buttons, labels, etc
	LPWORD pWord = reinterpret_cast<LPWORD>(dialogTemplate + 1);
	*pWord++ = 0; // No menu
	*pWord++ = 0; // Predefined dialog box class (by default)

	//Title
	LPWSTR title = reinterpret_cast<LPWSTR>(pWord);
	MultiByteToWideChar(CP_ACP, 0, windowTitle.c_str(), -1, title, numWChars);

	pWord += 1 + numWChars;

	*pWord++ = 0; //No more creation data. Only a window is created. Controls are manually created in WM_INITDIALOG.

	GlobalUnlock(hGlobal);
}

INT_PTR Dialog::ShowDialog(void* data)
{
	return DialogBoxIndirectParamW(hInstance, dialogTemplate, owner, dialogProc, reinterpret_cast<LPARAM>(data));
}

Dialog::~Dialog()
{
	if (hGlobal != nullptr) GlobalFree(hGlobal);
	hGlobal = nullptr;

	if (window != nullptr) DestroyWindow(window);
	window = nullptr;
}
