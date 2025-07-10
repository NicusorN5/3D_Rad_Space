#include "SoundControl.hpp"
#include "..\GDIFuncs.hpp"
#include "..\Windows\AssetManagerDialog.hpp"
#include <Engine3DRadSpace/Audio/Sound.hpp>

SoundControl::SoundControl(
	HWND owner,
	HINSTANCE hInstance,
	Engine3DRadSpace::Content::ContentManager *content,
	unsigned sound,
	const std::string &name,
	int x,
	int y
) :
	AssetControl(owner, hInstance, x, y, content, sound)
{
}

void SoundControl::HandleClick(HWND clickedWindow)
{
	if(clickedWindow == _button)
	{
		AssetManagerDialog assetManager(this->owner, this->instance, _content);
		auto r = assetManager.ShowDialog<Engine3DRadSpace::Audio::Sound>();

		if(r.ID != 0)AssetReference = r.ID;
	}
}
