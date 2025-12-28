#pragma once
#include <Engine3DRadSpace/Reflection/ReflectedField.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "..\Controls\Dialog.hpp"
#include "..\AssetListRenderer.hpp"
#include <semaphore>
#include <mutex>

class AssetManagerDialog : public Dialog
{
	HWND _assetList;

	HWND _searchLabel;
	HWND _searchBox;
	HWND _browseButton;

	HIMAGELIST _imageList;

	std::map<int, HBITMAP> _imageDict;

	Engine3DRadSpace::Content::ContentManager *_content;
	std::unique_ptr<AssetListRenderer> _renderer;

	Engine3DRadSpace::Reflection::UUID _assetType;
	const char* _fileFilter = nullptr;

	std::counting_semaphore<8> _imgSemaphore{ 8 };

	void _createForms();
	void _loadAssetIcons();
public:
	AssetManagerDialog(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content);

	AssetManagerDialog(AssetManagerDialog&) = delete;
	AssetManagerDialog(AssetManagerDialog&&) = delete;

	AssetManagerDialog &operator=(AssetManagerDialog&) = delete;
	AssetManagerDialog &operator=(AssetManagerDialog&&) = delete;

	template<Engine3DRadSpace::Content::AssetType T>
	Engine3DRadSpace::Content::AssetID<T> ShowDialog()
	{
		using namespace Engine3DRadSpace;
		using namespace Engine3DRadSpace::Content;
		using namespace Engine3DRadSpace::Internal;

		_assetType = AssetUUIDReader::GetUUID(Tag<T>{});
		_fileFilter = AssetUUIDReader::GetFileExtension(Tag<T>{});

		auto v = Dialog::ShowDialog(static_cast<void*>(this));
		return AssetID<T>(static_cast<unsigned>(v));
	}

	~AssetManagerDialog();

	friend INT_PTR WINAPI AssetManager_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

