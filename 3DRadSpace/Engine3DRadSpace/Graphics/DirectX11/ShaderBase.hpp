#pragma once
#include "../IShader.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;
	class ShaderCompiler;

	class ShaderBase : public IShader
	{
	protected:
		GraphicsDevice* _device;
		ShaderFeatureLevel _featureLevel;
		const char* _entry;

		Microsoft::WRL::ComPtr<ID3DBlob> _shaderBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob;
		Microsoft::WRL::ComPtr<ID3D11ShaderReflection> _reflector;

		std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> _constantBuffers;

		using Array_ValidConstantBuffers = std::array<ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT>;

		std::vector<std::unique_ptr<Reflection::IReflectedField>> _reflectedFields;

		Array_ValidConstantBuffers _validConstantBuffers(unsigned& numConstantBuffers);

		void _compileShader(const char* source, const char* target);
		void _compileShaderFromFile(const char* path, const char* target);
		void _reflectShader();

		ShaderBase(GraphicsDevice* device, const char* shaderSourceCode, const char* entry_function, ShaderFeatureLevel fl);
		ShaderBase(GraphicsDevice* device, const std::filesystem::path& path, const char* entry_function, ShaderFeatureLevel fl);
	public:
		ShaderBase(ShaderBase&) = delete;
		ShaderBase(ShaderBase&&) noexcept = default;

		ShaderBase& operator=(ShaderBase&) = delete;
		ShaderBase& operator=(ShaderBase&&) noexcept = default;

		void SetData(unsigned index, const void* data, size_t dataSize) override;
		ShaderFeatureLevel GetFeatureLevel() override;
		std::string GetEntryName() override;
		const char* GetCompilationErrorsAndWarnings() override;

		std::vector<Reflection::IReflectedField*> GetVariables() const override;
		void Set(const std::string& name, const void* data, size_t dataSize) override;

		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~ShaderBase() override = default;

		friend class ShaderCompiler;
	};
}