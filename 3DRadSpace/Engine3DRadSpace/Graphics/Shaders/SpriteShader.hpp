#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class DLLEXPORT SpriteShader : public Effect
	{
		class VertexShader : public IVertexShader
		{
		public:
			VertexShader(GraphicsDevice *device);
			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IFragmentShader
		{
		public:
			PixelShader(GraphicsDevice *device);
		};
	public:
		explicit SpriteShader(GraphicsDevice*device);

		void SetTexture(Texture2D *texture);
		void SetSamplerState(SamplerState *sampler);
	};
}