#include "EditObjectDialog.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

INT_PTR __stdcall EditObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static EditObjectDialog* eod = nullptr;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		eod = reinterpret_cast<EditObjectDialog*>(lParam);
		eod->window = hwnd;
		eod->createForms();

		SendMessageA(hwnd, WM_SETFONT, NULL, true);
		return 1;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_3DFACE + 1));
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_COMMAND:
	{
		switch(HIWORD(wParam))
		{
			case BN_CLICKED:
			{
				if(lParam == reinterpret_cast<LPARAM>(eod->_okButton))
				{
					eod->setObject();
					EndDialog(hwnd, IDOK);
					return 1;
				}
				if(lParam == reinterpret_cast<LPARAM>(eod->_cancelButton))
				{
					EndDialog(hwnd, IDCANCEL);
					return 1;
				}

				if (lParam == reinterpret_cast<LPARAM>(eod->_helpButton))
				{
					ShellExecuteA(hwnd, "open", eod->_helpUrl.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
				}

				eod->_propertyGrid->HandleClick(reinterpret_cast<HWND>(lParam));
				return 0;
			}
			default:
				return 0;
		}
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, IDCANCEL);
		return 1;
	}
	default:
		return 0;
	}
}

EditObjectDialog::EditObjectDialog(HWND owner, HINSTANCE hInstance, ReflectedObject *data, ContentManager *content, IObject *obj) :
	Dialog(owner, hInstance, EditObjectDialog_DlgProc, data->Name + " object"),
	_reflectedObject(data),
	_content(content),
	_object(obj),
	_helpButton(nullptr),
	_okButton(nullptr),
	_cancelButton(nullptr)
{
	assert(data != nullptr);
}

static std::unordered_map<std::string, int> attribMap =
{
	{"HelpURL", 1},
	{"Title", 2 },
	{"CustomWindow", 3}
};

void EditObjectDialog::createForms()
{
	_propertyGrid = std::make_unique<PropertyGrid>(window, hInstance, 3, 5, _object, _reflectedObject, _content);

	auto x = _propertyGrid->GetWidth() + 10;
	auto y = _propertyGrid->GetHeight() + 10;

	HDC hdc = GetDC(window);

	for (auto& refl : *_propertyGrid->GetRefl())
	{
		if(auto attr = dynamic_cast<Attribute*>(refl); attr != nullptr)
		{
			switch (attribMap[attr->FieldName()])
			{
			case 1:
				_helpUrl = attr->FieldDesc();
				break;
			case 2:
				SetWindowTextA(window, attr->FieldDesc().c_str());
				break;
			default:
				break;
			}
		}
	}

	int titleBarHeight = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER);

	SIZE size;
	GetTextExtentPoint32A(hdc, "Help", 4, &size);

	int buttonHeight = y;
	int height = 2 * titleBarHeight + buttonHeight + 5;

	_helpButton = CreateWindowExA(
		0,
		"Button",
		"Help",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10,
		buttonHeight,
		size.cx + 10,
		size.cy + 7,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	GetTextExtentPoint32A(hdc, "Cancel", 6, &size);
	
	int okButtonX = x - size.cx - 30;
	_okButton = CreateWindowExA(
		0,
		"Button",
		"OK",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		okButtonX,
		buttonHeight,
		size.cx + 10,
		size.cy + 7,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	_cancelButton = CreateWindowExA(
		0,
		"Button",
		"Cancel",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		okButtonX - size.cx - 10,
		buttonHeight,
		size.cx + 10,
		size.cy + 7,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	SetWindowPos(window, nullptr, 0, 0, x + 3, height, SWP_NOMOVE);
}

void EditObjectDialog::setObject()
{
	_object = _propertyGrid->GetEditedObject();
}

IObject* EditObjectDialog::ShowDialog()
{
	INT_PTR r = Dialog::ShowDialog(this);
	if (r == IDOK) return _object;
	return nullptr;
}