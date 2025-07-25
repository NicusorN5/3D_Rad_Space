#pragma once
#include "../IFragmentShader.hpp"
#include "..\IVertexShader.hpp"
#include "../RenderTarget.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a pixel shader that is applied to the backbuffer.
	/// </summary>
	/// <remarks>
	/// This is almost the same as IFragmentShader, but render target swaps are being done.
	/// A vertex shader doesn't need to be set to the pipeline, it is set by the PostProcessVertex class.
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT PostProcessEffect : public IFragmentShader
	{
	private:
		class PostProcessVertex : public IVertexShader
		{
			static inline InputLayoutElement _elements[] = {
				InputLayoutElement::Position_Vec2,
				InputLayoutElement::TextureCoordinate2D
			};

		public:
			PostProcessVertex(GraphicsDevice* device, ShaderFeatureLevel fl);
			std::span<InputLayoutElement> InputLayout() override;
		} _vertex;
	protected:
		PostProcessEffect(
			 GraphicsDevice* device, 
			 const char* shaderSource, 
			 const char* entryFunction, 
			 ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4
		 );

		 	 PostProcessEffect(
			 GraphicsDevice* device, 
			 const std::filesystem::path &shaderPath, 
			 const char* entryFunction, 
			 ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4
		 );

		Texture2D* _backbuffer_copy;
		Texture2D* _depthBuffer_copy;
	public:
		/// <summary>
		/// Is this effect enabled?
		/// </summary>
		bool Enabled = true;

		/// <summary>
		/// Applies the effect.
		/// </summary>
		virtual void Apply();
		/// <summary>
		/// Draws a screen quad containing the processed texture, usually the backbuffer.
		/// </summary>
		void Draw();

		virtual ~PostProcessEffect() = default;

		friend class PostProcessCollection;
	};
}