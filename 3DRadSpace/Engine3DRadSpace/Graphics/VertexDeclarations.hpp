/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/VertexDeclarations.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------

#pragma once
#include "../Math/Vector3.hpp"
#include "../Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct VertexPosition
	{
		Math::Vector3 Position;
	};

	struct VertexPositionColor
	{
		Math::Vector3 Position;
		Color Color;
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
		Color Color;
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
		Color Color;
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
		Color Color;
	};

	struct VertexPositionNormalBitangentUVColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Vector2 UV;
		Color Color;
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
		Color Color;
	};

	template <typename V>
	concept VertexDecl = requires(V v)
	{
		v.Position = Math::Vector3::Zero();
	} || requires(V v)
	{
		v.Position = Math::Vector2::Zero();
	};
}