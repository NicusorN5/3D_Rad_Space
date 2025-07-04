#include "EditorWindow.hpp"
#include "..\..\resource.h"
#include <fstream>
#include "..\HelperFunctions.hpp"
#include <d3d11.h>
#include <assert.h>
#include <ranges>

#include "AddObjectDialog.hpp"
#include "SettingsWindow.hpp"
#include "Engine3DRadSpace/Core/Logging/Exception.hpp"
#include <Engine3DRadSpace/Objects/ObjectList.hpp>
#include <Engine3DRadSpace/Objects/Gizmos/IGizmo.hpp>

#include "../AutoupdaterState.hpp"
#include "UpdateProgressWindow.hpp"
#include <Engine3DRadSpace\Objects\Objects.hpp>
#include <thread>
#include <Engine3DRadSpace\Projects\Serialization.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Internal;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Projects;

EditorWindow* gEditorWindow = nullptr;

void EditorWindow::_saveProject(const char* filename)
{
	if (filename == nullptr || strlen(filename) == 0)
	{
		char filebuff[_MAX_PATH]{};

		OPENFILENAMEA ofn{};
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = gEditorWindow->_mainWindow;
		ofn.lpstrTitle = "Save a 3DRadSpace project...";
		ofn.lpstrFile = filebuff;
		ofn.nMaxFile = _MAX_PATH;
		ofn.lpstrFilter = FileFilter;
		ofn.hInstance = gEditorWindow->_hInstance;

		if (GetSaveFileNameA(&ofn))
		{
			_writeProject(ofn.lpstrFile);
		}
		else if (GetLastError() != 0)
			MessageBoxA(gEditorWindow->_mainWindow, std::format("Error trying to create the save file dialog box! : {}", GetLastError()).c_str(), "Error!", MB_OK | MB_ICONWARNING);
	}
	else
	{
		_writeProject(filename);
	}
}

void EditorWindow::_writeProject(const char *fileName)
{
	_changesSaved = true;

	Serializer::SaveProject(editor->Objects.get(), editor->Content.get(), std::filesystem::path(fileName));
}

void EditorWindow::_findUpdate()
{
	if(!_changesSaved) _saveProject();

	const std::string updateFilePath = "UpdateInfo.txt";

	HRESULT r = URLDownloadToFileA(
		nullptr, //IUnknown pCaller
		"https://3dradspace.org/UpdateInfo/LastestVersion.txt", //const* char url
		updateFilePath.c_str(), //const char* filename
		BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE, //flags (MSDN says it's reserved, lol)
		nullptr //IBindStatusCallback
	);
	switch (r) //Check if downloading info succeded
	{
	case S_OK:
		break; //Continue to download setup
	case E_OUTOFMEMORY:
		MessageBoxA(_mainWindow, "Out of memory", "Update error", MB_ICONERROR | MB_OK);
		return;
	case INET_E_DOWNLOAD_FAILURE:
		MessageBoxA(_mainWindow, "Network error. Check your internet connection.", "Update error", MB_ICONERROR | MB_OK);
		return;
	case 0x800c0005: //The system cannot locate the resource specified.
		MessageBoxA(_mainWindow, "Network error. Domain is down", "Update error", MB_ICONERROR | MB_OK);
		return;
	default:
		MessageBoxA(_mainWindow, "Unknown error.", "Update error", MB_ICONERROR | MB_OK);
		return;
	}

	//Parse info file
	std::ifstream updateDataFile(updateFilePath);
	if (updateDataFile.bad() || updateDataFile.fail())
	{
		MessageBoxA(_mainWindow, "Failed to load the update information!", "Update error", MB_ICONERROR | MB_OK);
		return;
	}

	std::string version;
	std::string downloadPath;
	updateDataFile >> version >> downloadPath;

	updateDataFile.close();

	std::filesystem::remove(updateFilePath); //Delete info file

	//Check version
	if (version == EngineVersion)
	{
		MessageBoxA(_mainWindow, "No new updates were found.", "Update information", MB_ICONINFORMATION | MB_OK);
		return;
	}

	auto q1 = MessageBoxA(_mainWindow, "There's a new update found, would you like to download it?", "Update found!", MB_ICONQUESTION | MB_YESNO);
	if (q1 != IDYES) return;

	//Download the update in a separate thread.
	std::thread downloaderThread([downloadPath]()
		{
			Microsoft::WRL::ComPtr<AutoupdaterState> updaterState;
			AutoupdaterState::Create(updaterState.GetAddressOf());

			UpdateProgressWindow* downloadUIWindow = nullptr;
			//The downloader thread also owns the UI thread.
			std::thread downloaderUIThread([&updaterState, &downloadUIWindow]()
				{
					UpdateProgressWindow window(gEditorWindow->_hInstance, updaterState.Get());
					downloadUIWindow = &window;

					//Win32 message loop. Only read downloader status messages.
					MSG msg;
					while (GetMessageA(&msg, window.GetWindow(), 0, 0))
					{
						TranslateMessage(&msg);
						DispatchMessageA(&msg);
						if (window.Sync() == true) break;
					}
				});
			downloaderUIThread.detach(); //Run the UI at the same time with the downloader.

			HRESULT r = URLDownloadToFileA(nullptr, downloadPath.c_str(), "Setup.exe", BINDF_GETNEWESTVERSION, updaterState.Get());
			switch (r)
			{
			case S_OK:
			{
				const int answer = MessageBoxA(gEditorWindow->_mainWindow, "Would you like to update 3DRadSpace now?", "Download complete!", MB_ICONQUESTION | MB_YESNO);

				if (answer == IDYES)
				{
					const auto r2 = ShellExecuteA(nullptr, nullptr, "Setup.exe", nullptr, nullptr, SW_NORMAL);
					if (reinterpret_cast<INT_PTR>(r2) < 32)
						MessageBoxA(gEditorWindow->_mainWindow, "Failed to open the setup!", "Error installing update!", MB_ICONERROR | MB_OK);
					else
						gEditorWindow->_running = false;
				}
				break;
			}
			case E_OUTOFMEMORY:
				MessageBoxA(gEditorWindow->_mainWindow, "Out of memory.", "Error downloading setup", MB_ICONERROR | MB_OK);
				break;
			case INET_E_DOWNLOAD_FAILURE:
				MessageBoxA(gEditorWindow->_mainWindow, "Network error. Setup download was most likely interrupted by a network change.", "Error downloading setup", MB_ICONERROR | MB_OK);
				break;
			case E_ABORT:
				break;
			default:
				MessageBoxA(gEditorWindow->_mainWindow, "Unknown error.", "Error downloading setup", MB_ICONERROR | MB_OK);
				break;
			}
		});

	downloaderThread.detach();
}

HTREEITEM EditorWindow::_getSelectedListViewItem()
{
	HTREEITEM selectedItem = reinterpret_cast<HTREEITEM>(SendMessageA(
		gEditorWindow->_listBox,
		TVM_GETNEXTITEM,
		TVGN_CARET,
		reinterpret_cast<LPARAM>(nullptr)
	));

	return selectedItem;
}

std::pair<HTREEITEM, std::optional<unsigned>> EditorWindow::_getSelectedObjectID()
{
	HTREEITEM selectedItem = _getSelectedListViewItem();

	if(selectedItem == nullptr) return {nullptr, std::nullopt};

	TVITEMA item{};
	item.mask = LVIF_PARAM;
	item.hItem = selectedItem;
	SendMessageA(gEditorWindow->_listBox, TVM_GETITEMA, 0, reinterpret_cast<LPARAM>(&item));

	return {selectedItem, static_cast<unsigned>(item.lParam)};
}

void EditorWindow::_parseCmdArgs(const std::string &cmdArgs)
{
	for(const auto token : std::views::split(cmdArgs, "\""))
	{
		//remove "s from the beginning and end if they exist
		std::string path(token.begin(), token.end());
		if(path[0] == '"') path.erase(0, 1);
		if(path[path.length() - 1] == '"') path.erase(path.length() - 1, 1);

		if(std::filesystem::exists(path))
		{
			//open project
			//MessageBoxA(_mainWindow, (std::string("Opened project \r\n") + path).c_str(), "Test", MB_ICONINFORMATION | MB_OK);
		}
		else
		{
			std::unordered_map<std::string, int> dictCmdArgs =
			{
				{"-noautoupdater", 1}, //Disables checking for updates at startup
				{"-na", 1},
				{"-defaultsettings", 2}, //Uses the default settings
				{"-ds", 2},
				{"-play", 3}, //Plays a project
				{"-p", 3},
				{"-build", 4}, //Builds a project
				{"-b", 4}
			};

			for(const auto token2 : std::views::split(token, " "))
			{
				std::string t2str(token2.begin(), token2.end());

				switch(dictCmdArgs[t2str])
				{
					case 1:
					{
						Settings::StartupUpdate.Value = false;
						break;
					}
					case 2:
					{
						Settings::CameraSensitivity.Value = 5.0f;
						Settings::ShowGrid.Value = true;
						Settings::StartupUpdate.Value = true;
						break;
					}
					case 3:
					{
						break;
					}
					case 4:
					{
						break;
					}
					default: break;
				}
			}
		}
	}
}

EditorWindow::EditorWindow(HINSTANCE hInstance,const std::string &cmdArgs) :
	_hInstance(hInstance),
	_mainWindow(nullptr),
	_listBox(nullptr),
	_toolbar(nullptr),
	_running(true)
{
	gEditorWindow = this;
	//
	//Register the window class
	//
	WNDCLASSA wndclass{};
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = EditorWindow_WndProc;
	wndclass.lpszClassName = EditorWindowClassName;
	wndclass.hIcon = LoadIconA(hInstance,MAKEINTRESOURCEA(IDI_ICON1));
	wndclass.hCursor = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512)); //IDI_ARROW

	ATOM a = RegisterClassA(&wndclass);
	if(a == 0)
		throw Exception("Failed to register class!");
	
	//
	//Create the menu
	//
	HMENU recentProjectsMenu = CreateMenu();
	if(recentProjectsMenu == nullptr) throw Exception("Failed to create File > Recent files menu!");

	std::ifstream recent_projects(RecentProjectFile);
	//Create the file if it doesn't exist or if it is empty
	if (recent_projects.bad() || recent_projects.fail())
	{
		std::ofstream create_recent_projects(RecentProjectFile);
		create_recent_projects.close();

		AppendMenuA(recentProjectsMenu, MF_STRING, 0, "...");
	}
	//Loop each line
	for(int i = 0; recent_projects; i++)
	{
		std::string filename;
		std::getline(recent_projects, filename);
		if(!filename.empty())
			AppendMenuA(recentProjectsMenu, MF_STRING, CMD_OpenRecentFile1 + static_cast<UINT_PTR>(i), filename.c_str());
	}
	recent_projects.close();

	//Create the rest of the menu.
	HMENU fileMenu = CreateMenu();
	if(fileMenu == nullptr) 
		throw Exception("Failed to create the file menu!");

	AppendMenuA(fileMenu, MF_STRING, CMD_NewFile, "New Project (Ctrl+N)");
	AppendMenuA(fileMenu, MF_STRING, CMD_OpenFile, "Open Project (Ctrl+O)");
	AppendMenuA(fileMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(recentProjectsMenu), "Recent projects...");
	AppendMenuA(fileMenu, MF_STRING, CMD_SaveProject, "Save Project (Ctrl+S)");
	AppendMenuA(fileMenu, MF_STRING, CMD_SaveProjectAs, "Save Project As (Ctrl+Shift+S)");
	AppendMenuA(fileMenu, MF_STRING, CMD_PlayProject, "Play Project (Ctrl+P)");
	AppendMenuA(fileMenu, MF_STRING, CMD_BuildProject, "Build Project (Ctrl+Shift+B)");
	AppendMenuA(fileMenu, MF_STRING, CMD_Exit, "Exit (Alt+F4)");

	HMENU editMenu = CreateMenu();
	if(editMenu == nullptr)
		throw Exception("Failed to create the edit menu!");

	AppendMenuA(editMenu, MF_STRING, CMD_AddObject, "Add Object (Ctrl+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAsset, "Add Asset (Ctrl+Shift+N)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddPrefab, "Add Prefab (Ctrl+Shift+A)");
	AppendMenuA(editMenu, MF_STRING, CMD_AddAddon, "Add Addon");
	AppendMenuA(editMenu, MF_STRING, CMD_ResetCursor, "Reset the 3D cursor");

	HMENU viewMenu = CreateMenu();
	if(viewMenu == nullptr)
		throw Exception("Failed to create the view menu!");

	AppendMenuA(viewMenu, MF_STRING | MF_CHECKED, CMD_SwitchObjectList, "Objects list");
	AppendMenuA(viewMenu, MF_STRING | MF_UNCHECKED, CMD_SwitchObjectList, "Property grid");

	HMENU optionsMenu = CreateMenu();
	if(optionsMenu == nullptr)
		throw Exception("Failed to create the options menu!");

	AppendMenuA(optionsMenu, MF_STRING, CMD_Preferences, "Preferences");
	AppendMenuA(optionsMenu, MF_STRING, CMD_Update, "Search for updates");

	HMENU helpMenu = CreateMenu();
	if(helpMenu == nullptr)
		throw Exception("Failed to create the help menu!");

	AppendMenuA(helpMenu, MF_STRING,CMD_About, "About");
	AppendMenuA(helpMenu, MF_STRING, CMD_Documentation, "Documentation");
	AppendMenuA(helpMenu, MF_STRING, CMD_Homepage, "Homepage");
	AppendMenuA(helpMenu, MF_STRING, CMD_Github, "Github");

	HMENU mainMenu = CreateMenu();
	if(mainMenu == nullptr)
		throw Exception("Failed to create the main menu!");

	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(fileMenu), "File");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(editMenu), "Edit");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(viewMenu), "View");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(optionsMenu), "Options");
	AppendMenuA(mainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(helpMenu), "Help");

	//Create window
	_mainWindow = CreateWindowExA(
		WS_EX_ACCEPTFILES,
		EditorWindowClassName,
		"3DRadSpace v0.1.0a - Editor",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		nullptr,
		mainMenu,
		hInstance,
		nullptr
	);

	if(_mainWindow == nullptr)
		throw Exception("Failed to create the main window!");

	//Create controls
	_toolbar = CreateWindowExA(
		0,
		TOOLBARCLASSNAMEA,
		"",
		TBSTYLE_LIST | WS_CHILD,
		0,
		0,
		800,
		25,
		_mainWindow,
		nullptr,
		hInstance,
		nullptr
	);
	if(_toolbar == nullptr)
		throw Exception("Failed to create the toolbar!");

	HIMAGELIST toolbarImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 8, 1);
	if(toolbarImageList == nullptr)
		throw Exception("Failed to create the toolbar image list!");

	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON2)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON3)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON4)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON5)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON6)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON7)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON8)));
	ImageList_AddIcon(toolbarImageList, LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON9)));
	
	SendMessageA(_toolbar, TB_SETIMAGELIST, 0, (LPARAM)(toolbarImageList));
	SendMessageA(_toolbar, TB_LOADIMAGES, 0, (LPARAM)HINST_COMMCTRL);
	
	TBBUTTON tbButtons[8] =
	{
		{ 0, CMD_NewFile,  TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"New" },
		{ 1, CMD_OpenFile, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Open"},
		{ 2, CMD_SaveProject, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Save"},
		{ 3, CMD_SaveProjectAs, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Save As"},
		{ 4, CMD_OpenIDE, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Open IDE"},
		{ 5, CMD_BuildProject, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Build"},
		{ 6, CMD_PlayProject, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Play"},
		{ 7, CMD_Switch2D3D, TBSTATE_ENABLED, BTNS_AUTOSIZE, {0}, 0, (INT_PTR)L"Switch to 2D"},
	};
	
	SendMessageA(_toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessageA(_toolbar, TB_ADDBUTTONS, 8, (LPARAM)&tbButtons);
	
	SendMessageA(_toolbar, TB_AUTOSIZE, 0, 0);

	_listBox = CreateWindowExA(
		0,
		WC_TREEVIEWA,
		"",
		TVS_CHECKBOXES | WS_CHILD | WS_VISIBLE | WS_BORDER,
		0,
		0, 
		150,
		600,
		_mainWindow,
		nullptr,
		hInstance,
		nullptr
	);

	this->editor = std::make_unique<RenderWindow>(_mainWindow,_hInstance);

	_handleRenderWindow = static_cast<HWND>(this->editor->Window->NativeHandle());

	//Accelerator table
	acceleratorTable = LoadAcceleratorsA(hInstance, MAKEINTRESOURCEA(IDR_ACCELERATOR1));
	if(acceleratorTable == nullptr)
		throw Exception("Failed to create the accelerator table");
	
	ShowWindow(_mainWindow, SW_MAXIMIZE);
	ShowWindow(_toolbar, SW_NORMAL);
	ShowWindow(_listBox, SW_NORMAL);

	_parseCmdArgs(cmdArgs);

	if (Settings::StartupUpdate.Value)
		_findUpdate();
}

void EditorWindow::Run()
{
	//Modified code from Window::Run() so accelerators(keyboard shortcuts) are also translated.
	editor->Initialize();
	editor->Load();

	while (_running && this->editor)
	{
		MSG msg;
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAcceleratorA(_mainWindow, acceleratorTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		auto ts_u1 = std::chrono::steady_clock::now();
		editor->PostProcesses->DisableAll();
		editor->Update();
		auto ts_u2 = std::chrono::steady_clock::now();

		std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
		editor->Update_dt = uDiff.count();

		auto ts_d1 = std::chrono::steady_clock::now();

		this->editor->Device->SetViewport();
		this->editor->Device->Clear(editor->ClearColor);
		this->editor->Draw3D();
		this->editor->PostProcesses->ApplyAll();
		this->editor->Draw2D();
		this->editor->Device->Present();

		auto ts_d2 = std::chrono::steady_clock::now();

		std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
		editor->Draw_dt = dDiff.count();
	}
}

EditorWindow::~EditorWindow()
{
	DestroyWindow(this->_mainWindow);
	UnregisterClassA(EditorWindowClassName, _hInstance);
}

GraphicsDevice*EditorWindow::GetGraphicsDevice()
{
	return this->editor->Device.get();
}

Content::ContentManager *EditorWindow::GetContentManager()
{
	return editor->Content.get();
}

void EditorWindow::AddObject(IObject*obj)
{
	if(obj == nullptr) return;

	//Change editor state
	_changesSaved = false;

	unsigned objID = editor->Objects->Add(obj);

	//add item into the treeView control
	TVITEMA item{};
	item.mask = TVIF_TEXT | TVIF_PARAM;
	item.pszText = const_cast<char *>(obj->Name.c_str());
	item.cChildren = 0;
	item.lParam = objID;

	TVINSERTSTRUCTA insertStruct{};
	insertStruct.item = item;

	SendMessageA(_listBox, TVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&insertStruct));
}

bool EditorWindow::WarnNotSaved()
{
	if(_changesSaved == true) return true;

	int c =  MessageBoxA(_mainWindow, "Scene is not saved! Unsaved progress will be lost. Save the current work?", "Scene not saved", MB_ICONWARNING | MB_YESNOCANCEL);
	if(c == IDYES)
	{
		_saveProject(gEditorWindow->_currentFile);
		return true;
	}
	else if(c == IDNO) return true;
	else return false;
}

void EditorWindow::SelectObject(std::optional<unsigned> id)
{
	if(id.has_value())
	{
		editor->SelectObject(editor->Objects->operator[](id.value()));
	}
	else
	{
		editor->SelectObject(nullptr);
	}
}

void SetWorkingDirectory();

LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps{};
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CLOSE:
		{
			gEditorWindow->_running = false;
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_QUIT:
		{
			exit(0);
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case CMD_NewFile:
				case ACC_NEW_PROJECT:
				{
					if(gEditorWindow->WarnNotSaved())
					{
						gEditorWindow->editor->Content->Clear();
						gEditorWindow->editor->Objects->Clear();
						SendMessageA(gEditorWindow->_listBox, TVM_DELETEITEM, 0, reinterpret_cast<LPARAM>(TVI_ROOT));
						gEditorWindow->_changesSaved = true;
					}
					break;
				}
				case CMD_OpenFile:
				case ACC_OPEN_PROJECT:
				{
					char filebuff[_MAX_PATH]{};

					OPENFILENAMEA ofn{};
					ofn.lStructSize = sizeof(OPENFILENAMEA);
					ofn.hwndOwner = gEditorWindow->_mainWindow;
					ofn.lpstrTitle = "Open a 3DRadSpace project...";
					ofn.lpstrFile = filebuff;
					ofn.nMaxFile = _MAX_PATH;
					ofn.lpstrFilter = FileFilter;
					ofn.hInstance = gEditorWindow->_hInstance;

					if(GetOpenFileNameA(&ofn))
					{
						//open project file.
						gEditorWindow->_changesSaved = true;

						gEditorWindow->editor->Content->Clear();
						SetWorkingDirectory();
						Serializer::LoadProject(gEditorWindow->editor->Objects.get(), gEditorWindow->editor->Content.get(), filebuff);

						SendMessageA(gEditorWindow->_listBox, LVM_DELETEALLITEMS, 0, 0);

						for (int i = 0; auto& instance : *(gEditorWindow->editor->Objects))
						{
							auto object = instance.Object.get();

							TVITEMA item{};
							item.mask = TVIF_TEXT | TVIF_PARAM;
							item.pszText = const_cast<char*>(object->Name.c_str());
							item.cChildren = 0;
							item.lParam = i;

							TVINSERTSTRUCTA insertStruct{};
							insertStruct.item = item;

							SendMessageA(gEditorWindow->_listBox, TVM_INSERTITEMA, 0, reinterpret_cast<LPARAM>(&insertStruct));

							++i;
						}
					}
					else if(GetLastError() != 0)
						MessageBoxA(gEditorWindow->_mainWindow, std::format("Error trying to create the open file dialog box! : {}", GetLastError()).c_str(), "Test", MB_OK | MB_ICONWARNING);
					break;
				}

				case CMD_OpenRecentFile1:
					break;
				case CMD_OpenRecentFile1 + 1:
					break;
				case CMD_OpenRecentFile1 + 2:
					break;
				case CMD_OpenRecentFile1 + 3:
					break;
				case CMD_OpenRecentFile1 + 4:
					break;
				case CMD_OpenRecentFile1 + 5:
					break;
				case CMD_OpenRecentFile1 + 6:
					break;
				case CMD_OpenRecentFile1 + 7:
					break;
				case CMD_OpenRecentFile1 + 8:
					break;
				case CMD_OpenRecentFile1 + 9:
					break;

				case CMD_SaveProject:
				case ACC_SAVE_PROJECT:
					gEditorWindow->_saveProject(gEditorWindow->_currentFile);
					SetWorkingDirectory();
					break;
				case CMD_SaveProjectAs:
				case ACC_SAVE_PROJECT_AS:
					gEditorWindow->_saveProject();
					SetWorkingDirectory();
					break;
				case CMD_PlayProject:
				case ACC_PLAY_PROJECT:
					break;
				case CMD_BuildProject:
				case ACC_BUILD_PROJECT:
					break;
				case CMD_Exit:
				{
					if(gEditorWindow->WarnNotSaved()) gEditorWindow->_running = false;
					break;
				}
				case CMD_AddObject:
				case ACC_ADD_OBJECT:
				{
					AddObjectDialog dialog(gEditorWindow->_mainWindow, gEditorWindow->_hInstance, gEditorWindow->GetContentManager());
					auto obj = dialog.ShowDialog();
					if (obj != nullptr && obj != reinterpret_cast<void*>(IDCANCEL))
					{
						obj->InternalInitialize(gEditorWindow->editor.get());
						
						auto gizmo = obj->GetGizmo();
						if(gizmo != nullptr)
						{
							gizmo->Object = obj;
							gizmo->Load();
						}

						gEditorWindow->AddObject(obj);
					}
					break;
				}
				case CMD_AddAsset:
				case ACC_ADD_ASSET:
					break;
				case CMD_AddAddon:
				{
					char filebuff[_MAX_PATH]{};

					OPENFILENAMEA ofn{};
					ofn.lStructSize = sizeof(OPENFILENAMEA);
					ofn.hwndOwner = gEditorWindow->_mainWindow;
					ofn.lpstrTitle = "Open a 3DRadSpace project...";
					ofn.lpstrFile = filebuff;
					ofn.nMaxFile = _MAX_PATH;
					ofn.lpstrFilter = FileFilter;
					ofn.hInstance = gEditorWindow->_hInstance;

					if(GetOpenFileNameA(&ofn))
					{
						SetWorkingDirectory();
						Serializer::LoadProject(gEditorWindow->editor->Objects.get(), gEditorWindow->editor->Content.get(), filebuff);
					}
					else if(GetLastError() != 0)
						MessageBoxA(gEditorWindow->_mainWindow, std::format("Error trying to create the open file dialog box! : {}", GetLastError()).c_str(), "Test", MB_OK | MB_ICONWARNING);
					break;
				}
				case ACC_ADD_PREFAB:
					break;
				case CMD_ResetCursor:
					gEditorWindow->editor->Reset3DCursor();
					break;				
				case CMD_Preferences:
				{
					SettingsWindow wnd(gEditorWindow->_mainWindow, gEditorWindow->_hInstance);
					wnd.ShowDialog();
					break;
				}
				case CMD_Update:
				{
					gEditorWindow->_findUpdate();
					break;
				}
				case CMD_About:
					break;
				case CMD_Documentation:
					ShellExecuteA(gEditorWindow->_mainWindow, nullptr, "https://3dradspace.org/Documentation", nullptr, nullptr, SW_NORMAL);
					break;
				case CMD_Homepage:
					ShellExecuteA(gEditorWindow->_mainWindow, nullptr, "https://3dradspace.org", nullptr, nullptr, SW_NORMAL);
					break;
				case CMD_Github:
					ShellExecuteA(gEditorWindow->_mainWindow, nullptr, "https://github.com/3DRadSpace/3D_Rad_Space/", nullptr, nullptr, SW_NORMAL);
					break;
				case CMD_EditObject:
				{
					auto objID = gEditorWindow->_getSelectedObjectID();
					if(objID.second.has_value())
					{
						IObject *obj = gEditorWindow->editor->Objects->Find(objID.second.value());

						EditObjectDialog eod(
							gEditorWindow->_mainWindow,
							gEditorWindow->_hInstance,
							Internal::GetReflDataFromUUID(obj->GetUUID()),
							gEditorWindow->GetContentManager(),
							obj
						);

						//update the list view.
						auto new_obj = eod.ShowDialog();
						if(new_obj != reinterpret_cast<void *>(IDCANCEL) && new_obj != nullptr)
						{
							TVITEMA item{};
							item.mask = TVIF_TEXT;
							item.hItem = objID.first;

							SendMessageA(gEditorWindow->_listBox, TVM_GETITEMA, 0, reinterpret_cast<LPARAM>(&item));

							item.pszText = const_cast<char *>(new_obj->Name.c_str());
							SendMessageA(gEditorWindow->_listBox, TVM_SETITEMA, 0, reinterpret_cast<LPARAM>(&item));

							auto gizmo = obj->GetGizmo();
							if(gizmo != nullptr)
							{
								gizmo->Load();
							}
						}
					}
					break;
				}
				case CMD_DeleteObject:
				{
					auto objID = gEditorWindow->_getSelectedObjectID();
					if(objID.second.has_value())
					{
						gEditorWindow->editor->Objects->Remove(objID.second.value());

						HTREEITEM deletedItem = objID.first;
						HTREEITEM currItem = deletedItem;

						//Update the indexes of the following elements
						while(currItem != nullptr)
						{
							currItem = reinterpret_cast<HTREEITEM>(SendMessageA(gEditorWindow->_listBox, TVM_GETNEXTITEM, TVGN_NEXT, reinterpret_cast<LPARAM>(currItem)));

							TVITEMA item{};
							item.mask = TVIF_PARAM;
							item.hItem = currItem;

							SendMessageA(gEditorWindow->_listBox, TVM_GETITEMA, 0, reinterpret_cast<LPARAM>(&item)); //read the item data

							//update the item data
							item.lParam -= 1;
							SendMessageA(gEditorWindow->_listBox, TVM_SETITEMA, 0, reinterpret_cast<LPARAM>(&item));
						}

						//delete selected listView item
						SendMessageA(gEditorWindow->_listBox, TVM_DELETEITEM, 0, reinterpret_cast<LPARAM>(deletedItem));
					}
					break;
				}
				default: break;
			}
			break;
		}
		case WM_SIZE:
		{
			RECT rcWnd{};
			GetClientRect(hwnd, &rcWnd);
			int wndWidth = rcWnd.right - rcWnd.left;
			int wndHeight = rcWnd.bottom - rcWnd.top;

			RECT rcToolbar{};
			GetClientRect(gEditorWindow->_toolbar, &rcToolbar);
			int toolbarHeight = rcToolbar.bottom - rcToolbar.top;

			SetWindowPos(gEditorWindow->_listBox, nullptr, 0, toolbarHeight, 150, wndHeight - toolbarHeight, 0);
			SetWindowPos(gEditorWindow->_toolbar, nullptr, 0, 0, wndWidth, 25, 0);
			SetWindowPos(gEditorWindow->_handleRenderWindow, nullptr, 150, toolbarHeight, wndWidth - 150, wndHeight - toolbarHeight, 0);
			break;
		}
		case WM_DROPFILES:
		{
			auto drop = reinterpret_cast<HDROP>(wParam);
			char file[_MAX_PATH];
			int numFilesDropped = DragQueryFileA(drop, 0xFFFFFFFF, nullptr, 0u);

			for(int i = 0; i < numFilesDropped; i++)
			{
				DragQueryFileA(drop, i, file, _MAX_PATH);
				//handle dropped file
				//MessageBoxA(gEditorWindow->_mainWindow, file, "Dropped file", MB_ICONINFORMATION);
			}
			break;
		}
		case WM_NOTIFY:
		{
			auto notif = reinterpret_cast<NMHDR *>(lParam);
			switch(notif->code)
			{
				auto listBox_check_selectedItem = []()
				{
					auto selectedItem = reinterpret_cast<HTREEITEM>(SendMessageA(
						gEditorWindow->_listBox,
						TVM_GETNEXTITEM,
						TVGN_CARET,
						reinterpret_cast<LPARAM>(nullptr)
					));

					return selectedItem;
				};

				case NM_RCLICK:
				{
					if(notif->hwndFrom == gEditorWindow->_listBox)
					{
						if(listBox_check_selectedItem() == nullptr) return 0;

						HMENU objectMenu = CreatePopupMenu();
						if(objectMenu == nullptr) throw std::exception("Failed to create a popup menu!");
						
						AppendMenuA(objectMenu, MF_STRING, CMD_EditObject, "Edit object");
						AppendMenuA(objectMenu, MF_STRING, CMD_DeleteObject, "Delete object");
						
						POINT mousePos;
						GetCursorPos(&mousePos);

						BOOL r = TrackPopupMenu(objectMenu, TPM_LEFTALIGN, mousePos.x, mousePos.y, 0, gEditorWindow->_mainWindow, nullptr);
						if(!r) throw std::exception("Failed to open a popup menu!");

						return 1;
					}
					break;
				}
				case NM_DBLCLK:
				{
					if(notif->hwndFrom == gEditorWindow->_listBox)
					{
						if(listBox_check_selectedItem() == nullptr) return 0;

						auto objID = gEditorWindow->_getSelectedObjectID();
						if(objID.second.has_value())
						{
							gEditorWindow->SelectObject(objID.second.value());
						}
						else
						{
							gEditorWindow->SelectObject(std::nullopt);
						}
						return 1;
					}
					break;
				}
				default:
					return 0;
			}
			break;
		}
		default:
			break;
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}