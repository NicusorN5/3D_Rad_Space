#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	/// <summary>
	/// Represents a trivial 2D effect, only with vertex colouring.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT Blank_NoMatrix : public Effect
	{
		class TrivialVertexShader : public IVertexShader
		{
		public:
			explicit TrivialVertexShader(GraphicsDevice* device);

			virtual std::span<InputLayoutElement> InputLayout();
		};

		class TrivialPixelShader : public IFragmentShader
		{
		public:
			/// <summary>
			/// Constructs the effect.
			/// </summary>
			/// <param name="device">Graphics device.</param>
			explicit TrivialPixelShader(GraphicsDevice *device);
		};
	public:
		explicit Blank_NoMatrix(GraphicsDevice* device);
	};
}