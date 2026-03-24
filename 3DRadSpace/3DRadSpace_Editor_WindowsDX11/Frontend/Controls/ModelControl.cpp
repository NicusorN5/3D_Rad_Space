#include "ModelControl.hpp"
#include "..\GDIFuncs.hpp"
#include "..\HelperFunctions.hpp"
#include "TextureControl.hpp"
#include "..\Windows\AssetManagerDialog.hpp"
#include "../../Editor/SkinmeshPreviewer.hpp"
#include <shlobj_core.h>

static std::string GetThumbnailPath(const std::filesystem::path& assetPath)
{
	char appdataPath[_MAX_PATH] = {};
	if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appdataPath)))
	{
		auto relPath = assetPath.lexically_relative(GetExecutablePath());
		return std::string(appdataPath) + R"(\3DRadSpace\AssetImages\)" + relPath.string() + ".png";
	}
	return {};
}

ModelControl::ModelControl(
	HWND owner,
	HINSTANCE hInstance, 
	Engine3DRadSpace::Content::ContentManager* content,
	unsigned model,
	const std::string& name,
	int x,
	int y 
) : 
	AssetControl(owner, hInstance, x, y, content, model),
	_pictureBox(CreateWindowExA(
		0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_REALSIZECONTROL,
		x,
		y + _cy + 5,
		200,
		200,
		owner,
		nullptr,
		hInstance,
		nullptr
	))
{
	_cy += 205;

	unsigned imageWidth;
	unsigned imageHeight;
	if (AssetReference != 0)
	{
		auto thumbnailPath = GetThumbnailPath(content->GetAssetPath(AssetReference));
		if (!thumbnailPath.empty())
			_image = loadImageFromFile(thumbnailPath, imageWidth, imageHeight);
	}

	if (_image == nullptr)
		_image = loadImageFromFile("Data\\NoAsset.png", imageWidth, imageHeight);

	SetImage(_pictureBox,_image, imageWidth, imageHeight);

	constexpr std::string_view previewBtnText = "Preview";

	HDC hdc = GetDC(owner);
	SIZE textSize;
	GetTextExtentPointA(hdc, previewBtnText.data(), previewBtnText.size(), &textSize);

	_previewButton = CreateWindowExA(
		0,
		"Button",
		previewBtnText.data(),
		WS_VISIBLE | WS_CHILD,
		x + 10,
		y + _cy,
		200,
		textSize.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_cy += textSize.cy + 5;
}

HWND ModelControl::GetPictureBox() const noexcept
{
	return _pictureBox;
}

void ModelControl::HandleClick(HWND clickedHandle)
{
	if (clickedHandle == _pictureBox || clickedHandle == _button)
	{
		AssetManagerDialog assetManager(owner, instance, _content);
		AssetReference = assetManager.ShowDialog<Engine3DRadSpace::Content::Assets::ModelAsset>();
		if (AssetReference != 0)
		{
			unsigned w, h;
			auto thumbnailPath = GetThumbnailPath(_content->GetAssetPath(AssetReference));
			if (!thumbnailPath.empty())
				_image = loadImageFromFile(thumbnailPath, w, h);

			if (_image == nullptr)
				_image = loadImageFromFile("Data\\NoAsset.png", w, h);

			SetImage(_pictureBox, _image, w, h);
		}
	}
	if (clickedHandle == _previewButton)
	{
		if (AssetReference != 0)
		{
			std::thread previewThread([this](const std::filesystem::path &path)
			{
				if(!_previewOpen)
				{
					_previewOpen = true;
					auto previewer = SkinmeshPreviewer(path);
					previewer.Run();

					_previewOpen = false;
				}
				else ::MessageBeep(MB_ICONASTERISK);
			}, std::filesystem::path(_content->GetAssetPath(AssetReference).string()));
			previewThread.detach();
		}
	}
}

ModelControl::~ModelControl()
{
	if (_image != nullptr)
	{
		DeleteObject(_image);
		_image = nullptr;
	}
}
