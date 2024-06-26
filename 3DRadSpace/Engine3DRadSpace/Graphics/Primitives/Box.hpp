#pragma once

#include "../../Math/BoundingBox.hpp"
#include "../../Color.hpp"
#include "../ModelMeshPart.hpp"
#include "../../IDrawable3D.hpp"
#include "../Shaders/BlankShader.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Box : public IDrawable3D
	{
		Math::BoundingBox _box;
		Color _color;
		Math::Matrix4x4 _worldMat;

		GraphicsDevice *_device;

		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<IndexBuffer> _indices;

		std::shared_ptr<Shaders::BlankShader> _shader;

		std::array<VertexPositionColor, 8> _createVerts(const Math::BoundingBox &b, const Color &color);
	public:
		Box(GraphicsDevice *device,const Math::BoundingBox &b, Color color);

		Box(const Box &) = delete;
		Box(Box &&b) noexcept = default;

		Box &operator=(const Box &) = delete;
		Box &operator=(Box &&b) noexcept = default;

		Math::BoundingBox GetBoundingBox() const noexcept;
		void SetBoundingBox(const Math::BoundingBox &b);

		Color GetColor() const noexcept;
		void SetColor(const Color&color);

		void SetTransform(const Math::Matrix4x4 &m);

		VertexBufferV<VertexPositionColor>* GetVertexBuffer() const noexcept;
		IndexBuffer* GetIndexBuffer() const noexcept;

		virtual void Draw(Math::Matrix4x4 &view, Math::Matrix4x4 &projection, double dt) override;
	};
}