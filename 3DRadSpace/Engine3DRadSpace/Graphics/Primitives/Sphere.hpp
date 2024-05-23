#pragma once
#include "../../IDrawable3D.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Sphere : public IDrawable3D
	{
		GraphicsDevice *_device;
		std::unique_ptr<VertexBufferV<VertexPositionColor>> _vertices;
		std::unique_ptr<IndexBuffer> _indices;

		std::shared_ptr<Shaders::BlankShader> _shader;

		float _radius;
	public:
		Sphere(GraphicsDevice *device, float radius, Color color, unsigned resolution);

		Sphere(const Sphere &) = delete;
		Sphere(Sphere &&) noexcept = default;

		Sphere &operator=(const Sphere &) = delete;
		Sphere &operator=(Sphere &&) noexcept = default;

		Math::Matrix4x4 Transform;

		float GetRadius() const;

		virtual void Draw(Math::Matrix4x4 &view, Math::Matrix4x4 &projection, double dt) override;

	};
}