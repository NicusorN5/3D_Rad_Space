#pragma once
#include "AssetControl.hpp"
#include <Engine3DRadSpace/Reflection/ReflectedField.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>

class SoundControl : public AssetControl
{
public:
	SoundControl(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Content::ContentManager* content,
		unsigned sound,
		const std::string &name,
		int x,
		int y
	);

	SoundControl(SoundControl &) = delete;
	SoundControl &operator=(SoundControl &) = delete;

	SoundControl(SoundControl &&c) noexcept = default;
	SoundControl &operator=(SoundControl &&c) noexcept = default;

	virtual void HandleClick(HWND clickedWindow) override;

	~SoundControl() = default;
};