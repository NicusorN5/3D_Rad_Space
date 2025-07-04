#pragma once
#include "Texture2D.hpp"
#include "SamplerState.hpp"
#include "ShaderFeatureLevel.hpp"

namespace Engine3DRadSpace::Graphics
{
#ifdef USING_DX11
	using Array_ValidConstantBuffers = std::array<ID3D11Buffer *, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT>;
#endif

	/// <summary>
	/// Represents the base type of IVertexShader, IFragmentShader, IHullShader, et cetera...
	/// </summary>
	/// <remarks>
	/// 
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT IShader
	{
	protected:
		GraphicsDevice*_device;
		ShaderFeatureLevel _featureLevel;
		const char* _entry;
#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3DBlob> _shaderBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob;

		std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> _constantBuffers;

		Array_ValidConstantBuffers _validConstantBuffers(unsigned &numConstantBuffers);
#endif
		void _compileShader( const char* source, const char* target);
		void _compileShaderFromFile( const char* path, const char* target);

		IShader(GraphicsDevice* device, const char* shaderSourceCode, const char* entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
		IShader(GraphicsDevice* device, const std::filesystem::path& path, const char* entry, ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4);
	public:
		IShader(IShader&) = delete;
		IShader(IShader&&) noexcept = default;

		IShader& operator=(IShader&) = delete;
		IShader &operator=(IShader &&) noexcept = default;

		void SetData(unsigned index,const void *data, unsigned dataSize);
		virtual void SetTexture(unsigned index, Texture2D *texture) = 0;
		virtual void SetSampler(unsigned index, SamplerState *samplerState) = 0;
		virtual void SetShader() = 0;
		virtual void* GetHandle() const noexcept = 0;

		ShaderFeatureLevel GetFeatureLevel();
		std::string GetEntryName();

		const char* GetCompilationErrorsAndWarnings();

		virtual ~IShader() = default;

		friend class GraphicsDevice;
	};
}