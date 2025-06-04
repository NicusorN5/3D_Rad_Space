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
		Function,
		Custom,
	};

	using FieldRepresentation = std::vector<std::pair<FieldRepresentationType, std::string>>;

	template<typename T> FieldRepresentation GetFieldRepresentation() = delete; //Only default and useer-written allow GetFieldRepresentation() specializations.

	//GetFieldRepresentation() specializations
	template<> DLLEXPORT FieldRepresentation GetFieldRepresentation<void>();
	template<> DLLEXPORT FieldRepresentation GetFieldRepresentation<bool>();
	template<signed_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Integer,""}}; }
	template<unsigned_integer T> FieldRepresentation GetFieldRepresentation() { return {{FieldRepresentationType::Unsigned,""}}; }
	template<std::floating_point T> FieldRepresentation GetFieldRepresentation() { return {{ FieldRepresentationType::Float,""}}; }
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<std::string>();

	template<Content::AssetType T>
	using AssetIDType = Content::AssetID<T>;

	template<AssetIDType T>
	FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Custom,""} }; }
	
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Content::AssetID<Graphics::Texture2D>>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Content::AssetID<Content::Assets::Model3D>>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Content::AssetID<Content::Assets::Font>>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Content::AssetID<Content::Assets::SkyboxAsset>>();

	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Input::Key>();

	//FieldRepresentationType() specializations for mathematical types
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Vector2>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Point>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Vector3>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Vector4>();	
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Quaternion>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Color>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Rectangle>();
	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::RectangleF>();

	template<> FieldRepresentation DLLEXPORT GetFieldRepresentation<Math::Matrix4x4>();

	//template<typename F> requires std::is_function_v<F> || std::is_member_function_pointer_v<F>
	//FieldRepresentation GetFieldRepresentation() { return { {FieldRepresentationType::Function,""} };}

	template<typename T>
	concept ReflectableType = requires
	{
		GetFieldRepresentation<T>();
	};
}
