#pragma once
#include "../Effect.hpp"
#include "..\..\Math\Matrix4x4.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	/// <summary>
	/// Represents a trivial 3D effect, with vertex colouring.
	/// </summary>
	class DLLEXPORT BlankShader : public Effect
	{
		class VertexShader : public IVertexShader
		{
		public:
			explicit VertexShader(GraphicsDevice* device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IFragmentShader
		{
		public:
			explicit PixelShader(GraphicsDevice* device);
		};
		static inline InputLayoutElement elements[2] = { InputLayoutElement::Position_Vec3, InputLayoutElement::Color };

	public:
		/// <summary>
		/// Constructs the shader.
		/// </summary>
		/// <param name="device">Graphics context.</param>
		explicit BlankShader(GraphicsDevice* device);

		/// <summary>
		/// Sets the linear transformation used to render the primitives.
		/// </summary>
		/// <param name="matrix">A MVP (model-view-projection) linear transformation is required.</param>
		void SetTransformation(const Math::Matrix4x4 &matrix);
	};
}