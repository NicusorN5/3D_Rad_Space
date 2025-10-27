#pragma once
#include "../IShader.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;

	class E3DRSP_GRAPHICS_EXPORT DX11ShaderBase : public IShader
	{
	protected:
		GraphicsDevice* _device;
		ShaderFeatureLevel _featureLevel;
		const char* _entry;

		Microsoft::WRL::ComPtr<ID3DBlob> _shaderBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob;

		std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> _constantBuffers;

		using Array_ValidConstantBuffers = std::array<ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT>;

		Array_ValidConstantBuffers _validConstantBuffers(unsigned& numConstantBuffers);

		void _compileShader(const char* source, const char* target);
		void _compileShaderFromFile(const char* path, const char* target);

		DX11ShaderBase(GraphicsDevice* device, const char* shaderSourceCode, const char* entry_function, ShaderFeatureLevel fl);
		DX11ShaderBase(GraphicsDevice* device, const std::filesystem::path& path, const char* entry_function, ShaderFeatureLevel fl);
		
		DX11ShaderBase(DX11ShaderBase&) = delete;
		DX11ShaderBase(DX11ShaderBase&&) noexcept = default;

		DX11ShaderBase& operator=(DX11ShaderBase&) = delete;
		DX11ShaderBase& operator=(DX11ShaderBase&&) noexcept = default;
		
		~DX11ShaderBase() override = default;
	};
}