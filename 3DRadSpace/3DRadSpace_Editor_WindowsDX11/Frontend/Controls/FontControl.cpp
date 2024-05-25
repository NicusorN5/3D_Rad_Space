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
	AssetControl(owner, hInstance, x, y, content, font )
{

}

void FontControl::HandleClick(HWND clickedWindow)
{
	if (clickedWindow == _button)
	{
		AssetManagerDialog assetManager(owner, instance, _content);
		AssetReference = assetManager.ShowDialog<Engine3DRadSpace::Graphics::Font>();
		if (AssetReference != 0)
		{

		}
	}
}
