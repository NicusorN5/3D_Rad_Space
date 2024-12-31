#pragma once

#include "../../Math/BoundingBox.hpp"
#include "IPrimitive.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Box : public IPrimitive
	{
		Math::BoundingBox _box;
		Color _color;

	public:
		Box(GraphicsDevice *device,const Math::BoundingBox &b, Color color);

		static std::array<VertexPositionColor, 8> CreateVertices(const Math::BoundingBox &b, const Color &color);
		static std::array<unsigned, 36> CreateIndices();

		Box(const Box &) = delete;
		Box(Box &&b) noexcept = default;

		Box &operator=(const Box &) = delete;
		Box &operator=(Box &&b) noexcept = default;

		Math::BoundingBox GetBoundingBox() const noexcept;
		void SetBoundingBox(const Math::BoundingBox &b);

		Color GetColor() const noexcept;
		void SetColor(const Color&color);

		VertexBufferV<VertexPositionColor>* GetVertexBuffer() const noexcept;
		IndexBuffer* GetIndexBuffer() const noexcept;

		virtual void Draw3D() override;
	};
}