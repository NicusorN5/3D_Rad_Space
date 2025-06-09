#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class E3DRSP_GRAPHICS_EXPORT MeshHighlight : public Effect
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
		static inline InputLayoutElement element[] = {InputLayoutElement::Position_Vec3};

	public:
		/// <summary>
		/// Constructs the shader.
		/// </summary>
		/// <param name="device">Graphics context.</param>
		explicit MeshHighlight(GraphicsDevice* device);

		/// <summary>
		/// Sets the linear transformation used to render the primitives.
		/// </summary>
		/// <param name="matrix">A MVP (model-view-projection) linear transformation is required.</param>
		void SetTransformation(const Math::Matrix4x4 &matrix);

		void SetColor(Math::Color c);
	};
}