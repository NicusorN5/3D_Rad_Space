#include "Main.h"
#include "resource.h"

HWND MainWindow, RenderWindow;

const wchar_t* const MainWindowClassName = L"3DRADSPACE_MAIN_WINDOW";
const wchar_t* const EditorWindowClassName = L"3DRADSPACE_EDITOR_WINDOW";

int __stdcall wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR args, int nShowCmd)
{
	//load editor icon
	HICON hAppIcon = static_cast<HICON>(::LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 64, 64, LR_DEFAULTCOLOR));
	
	//Register editor class
	WNDCLASS wndclass;
	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.lpfnWndProc = WindowProcessMain;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = MainWindowClassName;
	wndclass.hIcon = hAppIcon;

	RegisterClass(&wndclass);

	//Register 3D window class
	WNDCLASS editorwndclass;
	memset(&editorwndclass, 0, sizeof(WNDCLASS));
	editorwndclass.lpfnWndProc = WindowProcessEditor;
	editorwndclass.hInstance = hInstance;
	editorwndclass.lpszClassName = EditorWindowClassName;
	editorwndclass.hIcon = hAppIcon;

	RegisterClass(&editorwndclass);

	//Create main window menu
	HMENU MainMenu = CreateMenu();
	
	HMENU FileMenu = CreateMenu();
	AppendMenuW(FileMenu, MF_STRING, MENU_NEWFILE, L"New project (Ctrl+N)");
	AppendMenuW(FileMenu, MF_STRING, MENU_OPENFILE, L"Open project (Ctrl+O)");
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILE, L"Save project (Ctrl+S)");
	AppendMenuW(FileMenu, MF_STRING, MENU_SAVEFILEAS, L"Save project as (Ctrl+Shift+S)");
	AppendMenuW(FileMenu, MF_STRING, MENU_PLAYPROJECT, L"Play project (Ctrl+p)");
	AppendMenuW(FileMenu, MF_STRING, MENU_COMPILEPROJECT, L"Build project (Ctrl+Shift+B)");
	AppendMenuW(FileMenu, MF_STRING, MENU_EXIT, L"Exit (Alt+F4)");
	
	HMENU ObjectMenu = CreateMenu();
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDOBJ, L"Add object (Ctrl+A)");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_ADDPROJECT, L"Add a addon");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_INSTALLFILES, L"Import resources");
	AppendMenuW(ObjectMenu, MF_STRING, MENU_RESETCURSOR, L"Reset 3D Cursor");

	HMENU OptionsMenu = CreateMenu();
	AppendMenuW(OptionsMenu, MF_STRING, MENU_UPDATECHECK, L"Check for updates...");
	AppendMenuW(OptionsMenu, MF_STRING, MENU_PREFERENCES, L"Preferences");

	HMENU HelpMenu = CreateMenu();
	AppendMenuW(HelpMenu, MF_STRING, MENU_ABOUT, L"About");
	AppendMenuW(HelpMenu, MF_STRING, MENU_DOCS, L"Documentation");
	AppendMenuW(HelpMenu, MF_STRING, MENU_HOMEPAGE, L"Homepage");
	AppendMenuW(HelpMenu, MF_STRING, MENU_FORUM, L"Forum");
	AppendMenuW(HelpMenu, MF_STRING, MENU_GITHUB, L"GitHub");

	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)FileMenu, L"File");
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)ObjectMenu, L"Edit");
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)OptionsMenu, L"Options");
	AppendMenuW(MainMenu, MF_POPUP, (UINT_PTR)HelpMenu, L"Help");

	//create windows
	MainWindow = CreateWindowExW(0, MainWindowClassName, L"3DRadSpace - Editor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 600, nullptr, MainMenu, hInstance, 0);
	RenderWindow = CreateWindowExW(0, EditorWindowClassName, L"not used", WS_CHILD, 0, 0, 800, 600, MainWindow, nullptr, hInstance, 0);

	RS_DX11::Game game(RenderWindow);
	ID3D11Device* device = game.GetDevice();
	ID3D11DeviceContext* context = game.GetDeviceContext();
	IDXGISwapChain* swapchain = game.GetSwapChain();

	ID3D11Texture2D* backtexture = nullptr;
	HRESULT r = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backtexture);
	if (backtexture == nullptr)
	{
		MessageBox(nullptr, L"Failed to create the back buffer texture ID3D11Texture2D.", L"Fatal error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	ID3D11RenderTargetView* MainRenderTarget = nullptr;
	device->CreateRenderTargetView(backtexture, nullptr, &MainRenderTarget);
	backtexture->Release();
	
	if (MainRenderTarget == nullptr)
	{
		MessageBox(nullptr, L"Failed to create the main render target.", L"Fatal error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	ID3D11Texture2D* StencilTexture;
	D3D11_TEXTURE2D_DESC StencilTxtDesc;
	memset(&StencilTxtDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	StencilTxtDesc.ArraySize = 1;
	StencilTxtDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	StencilTxtDesc.MipLevels = 1;
	StencilTxtDesc.Width = 800;
	StencilTxtDesc.Height = 600;
	StencilTxtDesc.SampleDesc.Count = 1;
	StencilTxtDesc.SampleDesc.Quality = 0;
	StencilTxtDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

	device->CreateTexture2D(&StencilTxtDesc,nullptr,&StencilTexture);

	if (StencilTexture == nullptr)
	{
		MessageBox(nullptr, L"Failed to create the depth stencil texture.", L"Fatal error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	D3D11_DEPTH_STENCIL_DESC StencilDesc;
	memset(&StencilDesc,0,sizeof(D3D11_DEPTH_STENCIL_DESC));
	StencilDesc.DepthEnable = true;
	StencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	StencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	StencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	StencilDesc.StencilEnable = true;
	StencilDesc.StencilReadMask = 0xFF;
	StencilDesc.StencilWriteMask = 0xFF;
	StencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	StencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	StencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	StencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	StencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	ID3D11DepthStencilState* DepthStencilState = nullptr;
	device->CreateDepthStencilState(&StencilDesc, &DepthStencilState);
	context->OMSetDepthStencilState(DepthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC StencilViewDesc;
	memset(&StencilViewDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	StencilViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	StencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;

	ID3D11DepthStencilView* DepthStencilView = nullptr;
	r = device->CreateDepthStencilView(StencilTexture, &StencilViewDesc, &DepthStencilView);

	if (DepthStencilView == nullptr)
	{
		MessageBox(nullptr, L"Failed to create ID3D11DepthSentcilView", L"Fatal error", MB_OK | MB_ICONERROR);
		//exit(1);
	}

	context->OMSetRenderTargets(1, &MainRenderTarget, DepthStencilView);

	D3D11_VIEWPORT Viewport;
	memset(&Viewport, 0, sizeof(D3D11_VIEWPORT));
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = 800;
	Viewport.Height = 600;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &Viewport);

	MSG m = { 0 };
	while (true)
	{
		while (PeekMessage(&m, nullptr, 0, 0, 1));
		{
			TranslateMessage(&m);
			DispatchMessageW(&m);
		}
		float cleancolor[] = { 0.0f,0.0f,0.0f,1.0f };
		context->ClearRenderTargetView(MainRenderTarget, cleancolor);
		swapchain->Present(1, 0);
	}
	return EXIT_SUCCESS;
}

LRESULT __stdcall WindowProcessMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			exit(0);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT sPaint;
			HDC h = BeginPaint(MainWindow, &sPaint);
			FillRect(h, &sPaint.rcPaint, CreateSolidBrush(RGB(255,255,255)));
			EndPaint(MainWindow, &sPaint);
			break;
		}
		case WM_SIZE:
		{
			ResizeWindows();
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case MENU_NEWFILE:
					break;
				case MENU_OPENFILE:
					break;
				case MENU_SAVEFILE:
					break;
				case MENU_SAVEFILEAS:
					break;
				case MENU_PLAYPROJECT:
					break;
				case MENU_COMPILEPROJECT:
					break;
				case MENU_EXIT:
				{
					exit(0);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	return DefWindowProcW(hwnd,msg,wParam,lParam);
}

LRESULT __stdcall WindowProcessEditor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			exit(0);
			break;
		}
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void ResizeWindows()
{
	RECT r = { 0 };
	int width = r.right - r.left;
	int height = r.bottom - r.top;
	GetWindowRect(MainWindow,&r);
	SetWindowPos(RenderWindow, nullptr, 0, 0, width, height, SWP_SHOWWINDOW);
}