#pragma once
#include "../IShader.hpp"
#include "../ShaderDesc.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a pixel shader that is applied to the backbuffer.
	/// </summary>
	/// <remarks>
	/// By default, copies of the back buffer and depth buffer are sent as textures to the specified Fragment/Pixel shader. Use <c>NotDepthAware = true</c> to only upload the backbuffer.
	/// </remarks>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT PostProcessEffect : public IShader
	{
	private:
		IShader* _vertex;
		IShader* _effect;

		ITexture2D* _backbuffer_copy;
		ITexture2D* _depthBuffer_copy;
	protected:
		IGraphicsDevice* _device;
	public:
		PostProcessEffect(IGraphicsDevice* device, ShaderDesc& effect);
		/// <summary>
		/// Is this effect enabled?
		/// </summary>
		bool Enabled = true;

		bool NotDepthAware = false;

		/// <summary>
		/// Applies the effect.
		/// </summary>
		virtual void Apply();
		/// <summary>
		/// Draws a screen quad containing the processed texture, usually the backbuffer.
		/// </summary>
		void Draw();

		void SetTexture(unsigned index, ITexture2D* texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;
		void SetSampler(unsigned index, ISamplerState* sampler) override;
		void SetData(unsigned index, const void* data, size_t size) override;
		void SetShader() override;

		std::vector<Reflection::IReflectedField*> GetVariables() const override;
		void Set(const std::string& name, const void* data, size_t dataSize) override;

		std::string GetEntryName() override;
		const char* GetCompilationErrorsAndWarnings() override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~PostProcessEffect() override = default;

		friend class PostProcessCollection;
	};
}