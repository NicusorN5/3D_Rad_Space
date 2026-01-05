#pragma once
#include "../IShader.hpp"
#include "DirectX11.h"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class GraphicsDevice;
	class ShaderCompiler;

	class ShaderBase : public IShader
	{
	protected:
		GraphicsDevice* _device;
		const char* _entry;

		Microsoft::WRL::ComPtr<ID3DBlob> _shaderBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> _errorBlob;

		struct ConstantBuffer
		{
			Microsoft::WRL::ComPtr<ID3D11Buffer> Handle;
			std::unique_ptr<std::byte[]> Buffer;
			size_t Size;
		};

		std::array<ConstantBuffer, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> _constantBuffers;

		using Array_ValidConstantBuffers = std::array<ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT>;

		std::vector<std::unique_ptr<Reflection::IReflectedField>> _reflectedFields;

		Array_ValidConstantBuffers _validConstantBuffers(unsigned& numConstantBuffers);
		void _createConstantBuffer(size_t idxBuffer, size_t buffSize, const void* data);

		void _compileShader(const std::string_view& source, const std::string_view& target);
		void _compileShaderFromFile(const std::filesystem::path& path, const std::string_view& target);
		void _reflectShader();

		ShaderBase(GraphicsDevice* device, const char* shaderSourceCode, const char* entry_function, const char* target);
		ShaderBase(GraphicsDevice* device, const std::filesystem::path& path, const char* entry_function, const char* target);
	public:
		ShaderBase(ShaderBase&) = delete;
		ShaderBase(ShaderBase&&) noexcept = default;

		ShaderBase& operator=(ShaderBase&) = delete;
		ShaderBase& operator=(ShaderBase&&) noexcept = default;

		void SetData(unsigned index, const void* data, size_t dataSize) override;
		std::string_view GetEntryName() const noexcept override;
		const char* GetCompilationErrorsAndWarnings() const noexcept override;

		std::vector<Reflection::IReflectedField*> GetVariables() const override;
		void Set(const std::string& name, const void* data, size_t dataSize) override;
		void SetShader() override;

		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~ShaderBase() override = default;

		friend class ShaderCompiler;
	};
}