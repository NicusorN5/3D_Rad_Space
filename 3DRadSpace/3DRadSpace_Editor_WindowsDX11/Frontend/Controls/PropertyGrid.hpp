#pragma once
#include "IControl.hpp"
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include <Engine3DRadSpace/Reflection/ReflectedObject.hpp>
#include <Engine3DRadSpace/Objects/IObject.hpp>

class PropertyGrid : public IControl
{
	Engine3DRadSpace::Content::ContentManager* _content;
	Engine3DRadSpace::Objects::IObject* _object;
	Engine3DRadSpace::Reflection::ReflectedObject* _refl;
	std::vector<std::variant<HWND, std::unique_ptr<IControl>>> windows;

	Engine3DRadSpace::Math::Point _size;
public:
	PropertyGrid(
		HWND owner,
		HINSTANCE hInstance,
		int x, 
		int y,
		Engine3DRadSpace::Objects::IObject* object,
		Engine3DRadSpace::Reflection::ReflectedObject* data,
		Engine3DRadSpace::Content::ContentManager* content
	);

	PropertyGrid(const PropertyGrid&) = delete;
	PropertyGrid(PropertyGrid&&) noexcept = default;

	PropertyGrid& operator=(const PropertyGrid&) = delete;
	PropertyGrid& operator=(PropertyGrid&&) noexcept = default;

	Engine3DRadSpace::Objects::IObject* GetEditedObject();
	Engine3DRadSpace::Reflection::ReflectedObject* GetRefl() const noexcept;

	int GetWidth() const noexcept;
	int GetHeight() const noexcept;

	void HandleClick(HWND clickedWindow) override;

	~PropertyGrid() override = default;
};