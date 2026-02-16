#pragma once
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct VertexPosition
	{
		Math::Vector3 Position;
	};

	struct VertexPositionColor
	{
		Math::Vector3 Position;
		Math::Color Color;
	};

	struct VertexPositionUV
	{
		Math::Vector3 Position;
		Math::Vector2 UV;
	};
	
	struct VertexPointUV
	{
		Math::Vector2 Position;
		Math::Vector2 UV;
	};

	struct VertexPositionNormalColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Color Color;
	};

	struct VertexPositionNormalUV
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector2 UV;
	};

	struct VertexPositionNormalUVColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector2 UV;
		Math::Color Color;
	};

	struct VertexPositionNormalBitangent
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
	};

	struct VertexPositionNormalBitangentColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Color Color;
	};

	struct VertexPositionNormalBitangentUVColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Vector2 UV;
		Math::Color Color;
	};

	struct VertexPositionNormalBitangentUV
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Vector2 UV;
	};

	struct VertexPointUVColor
	{
		Math::Vector2 Position;
		Math::Vector2 UV;
		Math::Color Color;
	};

	template <typename V>
	concept VertexDecl = requires(V v)
	{
		v.Position = Math::Vector4::Zero();
	} || requires(V v)
	{
		v.Position = Math::Vector3::Zero();
	} || requires(V v)
	{
		v.Position = Math::Vector2::Zero();
	};
}