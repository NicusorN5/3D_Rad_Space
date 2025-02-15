/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Primitives/IPrimitive.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "../../IDrawable3D.hpp"
#include "../../Math/Matrix4x4.hpp"
#include "../ModelMeshPart.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexDeclarations.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Base class for vertex coloured primitive shapes.
	/// </summary>
	class IPrimitive : public IDrawable3D
	{
	protected:
		IPrimitive(GraphicsDevice* device);

		GraphicsDevice *_device;
		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<IndexBuffer> _indices;

		std::shared_ptr<Shaders::BlankShader> _shader;

		Math::Matrix4x4 _mvp() const noexcept;
	public:
		/// <summary>
		/// Camera view matrix.
		/// </summary>
		Math::Matrix4x4 View;
		/// <summary>
		/// Camera projection matrix.
		/// </summary>
		Math::Matrix4x4 Projection;
		/// <summary>
		/// World transform, composed usually of Scale, Rotation, Translation.
		/// </summary>
		Math::Matrix4x4 Transform;

		virtual ~IPrimitive() = default;
	};
}