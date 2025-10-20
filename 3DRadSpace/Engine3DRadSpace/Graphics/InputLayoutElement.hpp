#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the type of a input layout element.
	/// </summary>
	enum class InputLayoutElement
	{
		Position_Vec2 = 0,
		Position_Vec3,
		Position_Vec4,

		PositionTransformed_Vec3,
		PositionTransformed_Vec4,

		Color,

		Normal_Vec3,
		Normal_Vec4,

		Tangent_Vec3,
		Tangent_Vec4,

		Bitangent_Vec3,
		Bitangent_Vec4,

		TextureCoordinate2D,
		TextureCoordinate3D,
		TextureCoordinate4D,

		BlendIndices,
		BlendWeights,
		PointSize,
	};
}