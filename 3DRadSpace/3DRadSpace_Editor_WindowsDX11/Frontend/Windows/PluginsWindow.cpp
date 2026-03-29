#include "PluginsWindow.hpp"

extern std::vector<Engine3DRadSpace::Plugins::PluginInfo> pluginInfos;

INT_PTR WINAPI PluginsWindow_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PluginsWindow* wndPlugins = nullptr;

	switch(msg)
	{
		case WM_INITDIALOG:
		{
			wndPlugins = reinterpret_cast<PluginsWindow*>(lParam);
			wndPlugins->window = hwnd;
			wndPlugins->createForms();
			return 1;
		}
		case WM_COMMAND:
			if(HIWORD(wParam) == LBN_SELCHANGE && reinterpret_cast<HWND>(lParam) == wndPlugins->pluginsListBox)
			{
				int sel = static_cast<int>(SendMessageA(wndPlugins->pluginsListBox, LB_GETCURSEL, 0, 0));
				if(sel != LB_ERR)
					wndPlugins->onPluginSelected(sel);
				return TRUE;
			}
			switch (LOWORD(wParam))
			{
			case IDOK:
				EndDialog(hwnd, IDOK);
				return TRUE;
			case IDCANCEL:
				EndDialog(hwnd, IDCANCEL);
				return TRUE;
			default:
				break;
			}
			if(HIWORD(wParam) == BN_CLICKED && reinterpret_cast<HWND>(lParam) == wndPlugins->btnOK)
			{
				EndDialog(hwnd, IDOK);
				return TRUE;
			}
			break;
		default:
			break;
	}
	return FALSE;
}

void PluginsWindow::createForms()
{
	pluginsListBox = CreateWindowExA(0,
		"ListBox",
		"",
		WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_BORDER,
		10, 10, 400, 400,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	for(const auto& plugin : pluginInfos)
	{
		SendMessageA(pluginsListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(plugin.Name));
	}

	pluginLabelName = CreateWindowExA(0,
		"Static",
		"Select a plugin from the list.",
		WS_VISIBLE | WS_CHILD,
		420, 10, 400, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginLabelVersion = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD,
		420, 40, 400, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginLabelAuthor = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD,
		420, 70, 400, 20,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginLabelDescription = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD,
		420, 100, 400, 270,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	pluginPictureBox = CreateWindowExA(0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP,
		420, 210, 200, 200,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	btnOK = CreateWindowExA(0,
		"Button",
		"OK",
		WS_VISIBLE | WS_CHILD,
		700, 380, 80, 30,
		window,
		nullptr,
		hInstance,
		nullptr
	);
}

void PluginsWindow::onPluginSelected(int index)
{
	SetWindowTextA(pluginLabelName, std::format("Name: {}", pluginInfos[index].Name).c_str());
	SetWindowTextA(pluginLabelVersion, std::format("Version: {}", pluginInfos[index].Version).c_str());
	SetWindowTextA(pluginLabelAuthor, std::format("Author: {}", pluginInfos[index].Author).c_str());
	SetWindowTextA(pluginLabelDescription, std::format("Description: {}", pluginInfos[index].Description).c_str());
}

PluginsWindow::PluginsWindow(
	HWND owner,
	HINSTANCE hInstance
) : Dialog(owner, hInstance, PluginsWindow_DlgProc, "Plugins", 400, 210)
{
}

void PluginsWindow::ShowDialog()
{
	Dialog::ShowDialog(static_cast<void*>(this));
}