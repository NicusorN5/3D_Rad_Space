#pragma once
#include "Libs.hpp"
#include "resource.h"
#include "AddObjectDialog.hpp"
#include "DownloadStatusWindow.hpp"

constexpr int MENU_NEWFILE = 300;
constexpr int MENU_OPENFILE = 301;
constexpr int MENU_SAVEFILE = 302;
constexpr int MENU_SAVEFILEAS = 303;
constexpr int MENU_PLAYPROJECT = 304;
constexpr int MENU_COMPILEPROJECT = 305;
constexpr int MENU_EXIT = 306;

constexpr int MENU_ADDOBJ = 307;
constexpr int MENU_ADDPROJECT = 308;
constexpr int MENU_RESETCURSOR = 309;
constexpr int MENU_IMPORTRESOURCES = 310;

constexpr int MENU_UPDATECHECK = 311;
constexpr int MENU_PREFERENCES = 312;

constexpr int MENU_ABOUT = 313;
constexpr int MENU_DOCS = 314;
constexpr int MENU_HOMEPAGE = 315;
constexpr int MENU_FORUM = 316;
constexpr int MENU_GITHUB = 317;

constexpr int MENU_SWITCH3D2D = 318;

constexpr int MENU_OPEN_IDE = 319;

constexpr const char* __3DRADSPACE_VERSION = "0.1.0";
constexpr const __rawstring __3DRADSPACE_FD_FILTER = TEXT("3DRadSpace Project (*.3drsp)\0*.3drsp");

const __rawstring const MainWindowClassName = TEXT("3DRADSPACE_MAIN_WINDOW");
const __rawstring const EditorWindowClassName = TEXT("3DRADSPACE_EDITOR_WINDOW");

LRESULT __stdcall WindowProcessMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WindowProcessEditor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace Engine3DRadSpace; 

class EditorWindow 
{
	Vector3 CameraPos;
	bool  ShouldExit;

	//Matrix View, Projection;
	DirectX::XMMATRIX View, Projection;

	std::unique_ptr<DirectX::Mouse> ptrMouse = std::make_unique<DirectX::Mouse>();
	Point pMouseDelta;
	float camRotX = 0.5, camRotY = -0.5;
	float camZoom = 5;

	std::unique_ptr<DirectX::CommonStates> CommonStates;
	std::unique_ptr<DirectX::BasicEffect> BasicEffect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> AxisPrimitive;

	std::unique_ptr<Game> game;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapchain;
	ID3D11InputLayout* colorured_line_inputlayout;

	std::unique_ptr<StencilState> stencil;

	std::vector<IObject*> IObjectList;

	Point resolution;
	Point screenCenter;
public:
	EditorWindow(const EditorWindow& w) = delete;
	EditorWindow(EditorWindow&& w) = delete;
	EditorWindow(HINSTANCE hInstance, PWSTR cmdArgs);

	HWND MainWindow, RenderWindow, ToolBarWindow, ObjectsListBox;
	HINSTANCE hGlobCurrentInst;
	static EditorWindow* g_EWindow;

	__stdstring CurrentFile;
	Vector3 _3DCursor;
	bool IsSaved, _3DMode;

	HACCEL AcceleratorTable; //Keyboard shortcuts

	DWORD errorcode;

	void RaiseInitializationError(DWORD err);
	void RenderUpdateLoop();

	void ResizeWindows();
	void CheckUpdate();
	void DownloadUpdate(char* link, char* version);

	void UpdateDiscordRichPresence();
	void StopDiscordRichPresence();

	Point GetRenderWindowResolution();
	Point GetDisplaySize();

	void __cdecl LostGDevice();

	void AddObject(IObject* object);
	void RemoveObject(size_t index);
	void RefresObjectList();

	void StartDiscordPresence();

	void ResetLoadedProject();
	bool ShowProjectNotSavedWarning();

	void OpenProject(__rawstring path);
	void SaveProject();
	void SaveProjectAs();

	void ExitEditor();
	void ExitWithErrorCode(DWORD err);

	~EditorWindow();
};