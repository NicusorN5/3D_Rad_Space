#include "SkyboxControl.hpp"
#include "../Windows/AssetManagerDialog.hpp"
#include <Engine3DRadSpace\Content\Assets\SkyboxAsset.hpp>

SkyboxControl::SkyboxControl(
	HWND owner,
	HINSTANCE hInstance,
	Engine3DRadSpace::Content::ContentManager* content,
	unsigned skybox,
	const std::string& name,
	int x,
	int y
) :
	TextureControl(owner, hInstance, content, skybox, name, x, y)
{
}

void SkyboxControl::HandleClick(HWND clickedWindow)
{
	if(clickedWindow == _pictureBox || clickedWindow == _button)
	{
		AssetManagerDialog assetManager(this->owner, this->instance, _content);
		auto r = assetManager.ShowDialog<Engine3DRadSpace::Content::Assets::SkyboxAsset>();

		if(r.ID != 0)
		{
			unsigned w;
			unsigned h;
			_image = loadImageFromFile(_content->GetAssetPath(r.ID).string(), w, h);
			SetImage(_pictureBox,_image, w, h);

			AssetReference = r.ID;
		}
	}
}