#pragma once
#include "IPrimitive.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../VertexBuffer.hpp"
#include "../IndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class DLLEXPORT Sphere : public IPrimitive
	{
		float _radius;
	public:
		Sphere(GraphicsDevice *device, float radius, Color color, unsigned resolution);

		Sphere(const Sphere &) = delete;
		Sphere(Sphere &&) noexcept = default;

		Sphere &operator=(const Sphere &) = delete;
		Sphere &operator=(Sphere &&) noexcept = default;

		Math::Matrix4x4 Transform;

		float GetRadius() const noexcept;

		void Draw3D() override;
	};
}