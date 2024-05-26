#pragma once
#include "AssetControl.hpp"

class FontControl : public AssetControl
{
	//TODO: make _image and _bitmap part of AssetControl
	HBITMAP _image;
	HWND _pictureBox;
public:
	FontControl(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Content::ContentManager* content,
		unsigned font,
		const std::string& name,
		int x,
		int y
	);

	void HandleClick(HWND clickedWindow) override;
};

void SetImage(HWND _pictureBox, HBITMAP _image, unsigned width, unsigned height);