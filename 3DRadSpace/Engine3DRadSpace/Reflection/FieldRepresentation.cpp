#include "FieldRepresentation.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Audio;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Reflection;

template<> FieldRepresentation Reflection::GetFieldRepresentation<void>()
{
	return {{ FieldRepresentationType::Unknown, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<bool>()
{
	return {{ FieldRepresentationType::Boolean, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<std::string>()
{
	return {{ FieldRepresentationType::String, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<TextureAsset>>()
{
	return {{FieldRepresentationType::Image, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<ModelAsset>>()
{
	return {{FieldRepresentationType::Model, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<FontAsset>>()
{
	return { {FieldRepresentationType::Font, ""} };
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<SkyboxAsset>>()
{
	return {{FieldRepresentationType::Skybox, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<AssetID<Sound>>()
{
	return {{FieldRepresentationType::Sound, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Key>()
{
	return {{FieldRepresentationType::Key, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Vector2>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y" }
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Point>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y" }
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Point3>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y"},
		{ FieldRepresentationType::Integer, "Z"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Point4>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y"},
		{ FieldRepresentationType::Integer, "Z"},
		{ FieldRepresentationType::Integer, "W"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Vector3>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Z"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Vector4>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Z"},
		{ FieldRepresentationType::Float, "W"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Quaternion>() //Quaternions will be constructed from Euler angles.
{
	return {{ FieldRepresentationType::Quaternion, ""}};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Color>()
{
	return
	{
		{ FieldRepresentationType::Color, ""}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Math::Rectangle>()
{
	return
	{
		{ FieldRepresentationType::Integer, "X"},
		{ FieldRepresentationType::Integer, "Y"},
		{ FieldRepresentationType::Integer, "Width"},
		{ FieldRepresentationType::Integer, "Height"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<RectangleF>()
{
	return
	{
		{ FieldRepresentationType::Float, "X"},
		{ FieldRepresentationType::Float, "Y"},
		{ FieldRepresentationType::Float, "Width"},
		{ FieldRepresentationType::Float, "Height"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<Matrix4x4>()
{
	return
	{
		{ FieldRepresentationType::Float, "M11"},
		{ FieldRepresentationType::Float, "M12"},
		{ FieldRepresentationType::Float, "M13"},
		{ FieldRepresentationType::Float, "M14"},

		{ FieldRepresentationType::Float, "M21"},
		{ FieldRepresentationType::Float, "M22"},
		{ FieldRepresentationType::Float, "M23"},
		{ FieldRepresentationType::Float, "M24"},

		{ FieldRepresentationType::Float, "M31"},
		{ FieldRepresentationType::Float, "M32"},
		{ FieldRepresentationType::Float, "M33"},
		{ FieldRepresentationType::Float, "M34"},

		{ FieldRepresentationType::Float, "M41"},
		{ FieldRepresentationType::Float, "M42"},
		{ FieldRepresentationType::Float, "M43"},
		{ FieldRepresentationType::Float, "M44"}
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<UPoint>()
{
	return
	{
		{ FieldRepresentationType::Unsigned, "X"},
		{ FieldRepresentationType::Unsigned, "Y" }
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<UPoint3>()
{
	return
	{
		{ FieldRepresentationType::Unsigned, "X"},
		{ FieldRepresentationType::Unsigned, "Y" },
		{ FieldRepresentationType::Unsigned, "Z" },
	};
}

template<> FieldRepresentation Reflection::GetFieldRepresentation<UPoint4>()
{
	return
	{
		{ FieldRepresentationType::Unsigned, "X"},
		{ FieldRepresentationType::Unsigned, "Y" },
		{ FieldRepresentationType::Unsigned, "Z" },
		{ FieldRepresentationType::Unsigned, "W" }
	};
}
