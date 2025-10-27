#pragma once
#include "../IFragmentShader.hpp"
#include "../IVertexShader.hpp"
#include "../IRenderTarget.hpp"
#include "../InputLayoutElement.hpp"
#include "../ShaderDesc.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a pixel shader that is applied to the backbuffer.
	/// </summary>
	/// <remarks>
	/// This is almost the same as IFragmentShader, but render target swaps are being done.
	/// A vertex shader doesn't need to be set to the pipeline, it is set by the PostProcessVertex class.
	/// </remarks>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT PostProcessEffect : public IFragmentShader
	{
	private:
		IVertexShader* _vertex;
	protected:
		PostProcessEffect(IGraphicsDevice* device, const ShaderDesc& desc);

		IGraphicsDevice* _device;
		ITexture2D* _backbuffer_copy;
		ITexture2D* _depthBuffer_copy;
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