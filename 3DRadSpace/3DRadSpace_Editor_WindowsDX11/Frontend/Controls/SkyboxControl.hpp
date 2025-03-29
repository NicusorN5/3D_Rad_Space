#pragma once
#include "TextureControl.hpp"

class SkyboxControl: public TextureControl
{
public:
	SkyboxControl(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Content::ContentManager* content,
		unsigned texture,
		const std::string& name,
		int x,
		int y
	);

	void HandleClick(HWND clickedWindow) override;
};