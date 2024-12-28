#pragma once
#include "../IPixelShader.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class PostProcessEffect : public IFragmentShader
	{
	protected:
		 PostProcessEffect(
			 GraphicsDevice* device, 
			 const char* shaderSource, 
			 const char* entryFunction, 
			 ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4
		 );
	public:
		virtual void Apply();
		virtual ~PostProcessEffect() = default;
	};
}