#pragma once
#include "../Core/Libs.hpp"
#include "../Math/Color.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Rectangle.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Content/Assets/Model3D.hpp"
#include "../Content/Assets/Font.hpp"
#include "../Content/Assets/SkyboxAsset.hpp"
#include "../Input/Keyboard.hpp"
#include "../Core/Concepts.hpp"
#include "../Content/AssetID.hpp"
#include "../Core/GetSet.hpp"
#include "../Audio/Sound.hpp"

namespace Engine3DRadSpace
{
	class IObject;
}
namespace Engine3DRadSpace::Reflection
{
	enum class FieldRepresentationType
	{
		Unknown,
		Boolean,
		Integer,
		Unsigned,
		Float,
		Quaternion,
		String,
		Image,
		Model,
		Font,
		Key,
		Enum,
		Color,
		Skybox,
		Sound,
		Function,
		Custom,
	};

	using FieldRepresentation = std::vector<std::pair<FieldRepresentationType, std::string>>;

	template<typename T> FieldRepresentation GetFieldRepresentation() = delete; //Only default and useer-written allow GetFieldRepresentation() specializations.

	//GetFieldRepresentation() specializations
	template<> E3DRSP_REFLECTION_EXPORT FieldRepresentation GetFieldRepresentation<void>();
	template<> E3DRSP_REFLECTION_EXPORT FieldRepresentation GetFieldRepresentation<bool>();
	template<signed_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Integer,""}}; }
	template<unsigned_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Unsigned,""}}; }
	template<std::floating_point T> FieldRepresentation GetFieldRepresentation() { return {{ FieldRepresentationType::Float,""}}; }
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<std::string>();

	template<Content::AssetType T>
	using AssetIDType = Content::AssetID<T>;

	template<AssetIDType T>
	FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Custom,""} }; }
	
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Content::AssetID<Graphics::Texture2D>>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Content::AssetID<Content::Assets::Model3D>>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Content::AssetID<Content::Assets::Font>>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Content::AssetID<Content::Assets::SkyboxAsset>>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Content::AssetID<Audio::Sound>>();

	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Input::Key>();

	//FieldRepresentationType() specializations for mathematical types
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Vector2>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Point>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Vector3>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Vector4>();	
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Quaternion>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Color>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Rectangle>();
	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::RectangleF>();

	template<> FieldRepresentation E3DRSP_REFLECTION_EXPORT GetFieldRepresentation<Math::Matrix4x4>();

	//template<typename F> requires std::is_function_v<F> || std::is_member_function_pointer_v<F>
	//FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Function,""} };}

	//template<template<typename, typename, auto, auto> typename GetSetType, typename T, typename C, auto G, auto S> 
	//FieldRepresentation GetFieldRepresentation()
	//requires std::is_same_v<GetSet<T, C, G, S>, GetSetType<T, C, G, S>>
	//{
	//	return GetFieldRepresentation<T>();
	//}

	template<typename T>
	concept ReflectableType = requires
	{
		GetFieldRepresentation<T>();
	};
}
