#pragma once
#include "../IFragmentShader.hpp"
#include "..\IVertexShader.hpp"
#include "../RenderTarget.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a pixel shader that is applied to the backbuffer.
	/// </summary>
	class DLLEXPORT PostProcessEffect : public IFragmentShader
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

		void _setRenderSurface(GraphicsDevice* device);
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
	public:
		bool Enabled = true;

		std::shared_ptr<RenderTarget> _renderSurface;
		std::shared_ptr<Texture2D> _bkbuff_cpy;

		virtual void Apply();
		void Draw();

		virtual ~PostProcessEffect();
	};
}