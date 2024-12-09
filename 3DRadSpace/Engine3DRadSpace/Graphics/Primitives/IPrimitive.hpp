#pragma once
#include "../../IDrawable3D.hpp"
#include "../../Math/Matrix4x4.hpp"
#include "../ModelMeshPart.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexDeclarations.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
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
		Math::Matrix4x4 View;
		Math::Matrix4x4 Projection;
		Math::Matrix4x4 Transform;

		virtual ~IPrimitive() = default;
	};
}