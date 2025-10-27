#include "EffectAsset.hpp"
#include "../../Graphics/Effect.hpp"
#include "../../Graphics/ShaderDesc.hpp"
#include "../../Graphics/IGraphicsDevice.hpp"
#include "../../Core/Logging/ServiceBadCastException.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;

std::array<ShaderDescFile, 5> ShaderAsset::_createDesc(
	const std::filesystem::path& path,
	ShaderFeatureLevel featureLevel
)
{
	std::array<ShaderDescFile, 5> descs = {
		ShaderDescFile(path, "VSMain", ShaderType::VertexShader, featureLevel),
		ShaderDescFile(path, "PSMain", ShaderType::FragmentShader, featureLevel),
		ShaderDescFile(path, "HSMain", ShaderType::HullShader, featureLevel),
		ShaderDescFile(path, "DSMain", ShaderType::DomainShader, featureLevel),
		ShaderDescFile(path, "GSMain", ShaderType::GeometryShader, featureLevel)
	};

	return descs;
}

ShaderAsset::ShaderAsset(IService* service, const std::filesytem::path& path, ShaderFeatureLevel featureLevel) :
	_shader(nullptr)
{
	_device = dynamic_cast<IGraphicsDevice*>(service);
	if (_device == nullptr)
	{
		throw Logging::ServiceBadCastException<IGraphicsDevice>();
	}

	auto desc = _createDesc(path, featureLevel);

	_device->ShaderCompiler()->CompileEffect(&desc.data());
}

ShaderAsset::ShaderAsset(Internal::AssetUUIDReader) :
	_shader(nullptr)
{
}

Reflection::UUID ShaderAsset::GetUUID() const noexcept
{
	// {028F20CF-0008-47E6-8E87-6E383AFAA916}
	return { 0x28f20cf, 0x8, 0x47e6, { 0x8e, 0x87, 0x6e, 0x38, 0x3a, 0xfa, 0xa9, 0x16 } };
}
const char* ShaderAsset::FileExtension() const noexcept;
{
	return "All supported shaders(*.hlsl;*.fx)\0*.hlsl;*.fx;\0"
		"*.hlsl\0HLSL shader (*.hlsl)\0"
		"*.fx\0FX shader (*.fx)\0"
		"*.*\0All Files (*.*)\0\0";
}

std::type_index ShaderAsset::InitializationService() const noexcept
{
	return typeid(IGraphicsDevice);
}

Effect* ShaderAsset::operator->() const noexcept
{
	return _shader.get();
}

Effect& ShaderAsset::operator() noexcept
{
	return *_shader;
}