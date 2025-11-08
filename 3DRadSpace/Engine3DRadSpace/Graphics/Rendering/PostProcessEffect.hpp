#pragma once
#include "../IShader.hpp"
#include "../InputLayoutElement.hpp"
#include "../ShaderDesc.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a pixel shader that is applied to the backbuffer.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT PostProcessEffect : public IShader
	{
	private:
		IShader* _vertex;
		std::unique_ptr<IShader> _effect;
	protected:
		IGraphicsDevice* _device;
		ITexture2D* _backbuffer_copy;
		ITexture2D* _depthBuffer_copy;
	public:
		PostProcessEffect(IGraphicsDevice* device, const ShaderDesc& desc);
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

		void SetTexture(unsigned index, ITexture2D* texture) override;
		void SetTextures(std::span<ITexture2D*> textures) override;
		void SetSampler(unsigned index, ISamplerState* sampler) override;
		void SetData(unsigned index, const void* data, size_t size) override;
		void SetShader() override;

		std::vector<Reflection::IReflectedField*> GetVariables() const override;
		void Set(const std::string& name, const void* data, size_t dataSize) override;

		ShaderFeatureLevel GetFeatureLevel() override;
		std::string GetEntryName() override;
		const char* GetCompilationErrorsAndWarnings() override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~PostProcessEffect() override = default;

		friend class PostProcessCollection;
	};
}