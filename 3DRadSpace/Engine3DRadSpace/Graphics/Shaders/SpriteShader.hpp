#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	/// <summary>
	/// Represents the main shader used by SpriteBatch to render 2D sprites. Textured and vertex colouring are supported.
	/// </summary>
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
		/// <summary>
		/// Constructs this effect.
		/// </summary>
		/// <param name="device">Device handle</param>
		explicit SpriteShader(GraphicsDevice*device);

		/// <summary>
		/// Sets the texture, usually a sprite.
		/// </summary>
		/// <param name="texture">Image</param>
		void SetTexture(Texture2D *texture);
		/// <summary>
		/// Sets the texture sampler.
		/// </summary>
		/// <param name="sampler">Texture sampler.</param>
		void SetSamplerState(SamplerState *sampler);
	};
}