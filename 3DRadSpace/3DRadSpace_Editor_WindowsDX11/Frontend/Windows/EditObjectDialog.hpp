#pragma once
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "..\Controls\Dialog.hpp"
#include "..\Controls\PropertyGrid.hpp"
#include <variant>

class EditObjectDialog : public Dialog
{
	std::unique_ptr<PropertyGrid> _propertyGrid;

	Engine3DRadSpace::Reflection::ReflectedObject* _reflectedObject;
	Engine3DRadSpace::Content::ContentManager* _content;
	Engine3DRadSpace::Objects::IObject* _object;

	HWND _helpButton;
	HWND _okButton;
	HWND _cancelButton;

	std::string _helpUrl = "https://3dradspace.github.io/docs/objects.html";

	void createForms();
	void setObject();
public:
	EditObjectDialog(
		HWND owner,
		HINSTANCE hInstance, 
		Engine3DRadSpace::Reflection::ReflectedObject *data,
		Engine3DRadSpace::Content::ContentManager* content,
		Engine3DRadSpace::Objects::IObject *object = nullptr
	);

	[[nodiscard]] Engine3DRadSpace::Objects::IObject* ShowDialog();

	~EditObjectDialog() = default;

	friend INT_PTR WINAPI EditObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};