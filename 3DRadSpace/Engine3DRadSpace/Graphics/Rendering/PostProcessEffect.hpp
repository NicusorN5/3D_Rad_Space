#pragma once
#include "../IFragmentShader.hpp"
#include "..\IVertexShader.hpp"

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
	protected:
		 PostProcessEffect(
			 GraphicsDevice* device, 
			 const char* shaderSource, 
			 const char* entryFunction, 
			 ShaderFeatureLevel fl = ShaderFeatureLevel::DX_V4
		 );
	public:
		bool Enabled = true;

		virtual void Apply();
		void Draw();

		virtual ~PostProcessEffect() = default;
	};
}