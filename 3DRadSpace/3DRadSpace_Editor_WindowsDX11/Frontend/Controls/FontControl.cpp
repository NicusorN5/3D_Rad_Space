#include "FontControl.hpp"
#include "../Windows/AssetManagerDialog.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

FontControl::FontControl(
	HWND owner,
	HINSTANCE hInstance,
	ContentManager* content,
	unsigned font,
	const std::string& name,
	int x,
	int y
) :
	AssetControl(owner, hInstance, x, y, content, font),
	_pictureBox(CreateWindowExA(
		0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_REALSIZECONTROL,
		x,
		y,
		200,
		200,
		owner,
		nullptr,
		hInstance,
		nullptr
	)),
	_image(nullptr)
{
	unsigned imageWidth;
	unsigned imageHeight;

	if (AssetReference != 0)
		_image = loadImageFromFile(_content->GetAssetPath(AssetReference).string(), imageWidth, imageHeight);
	else
		_image = loadImageFromFile("Data\\NoAsset.png", imageWidth, imageHeight);

	SetImage(_pictureBox, _image, imageWidth, imageHeight);

	_cy += 205;
}

void FontControl::HandleClick(HWND clickedWindow)
{
	if (clickedWindow == _pictureBox || clickedWindow == _button)
	{
		AssetManagerDialog assetManager(this->owner, this->instance, _content);
		auto r = assetManager.ShowDialog<Engine3DRadSpace::Content::Assets::Font>();

		if (r.ID != 0)
		{
			unsigned w;
			unsigned h;
			_image = loadImageFromFile(_content->GetAssetPath(r.ID).string(), w, h);
			SetImage(_pictureBox, _image, w, h);

			AssetReference = r.ID;
		}
	}
}
