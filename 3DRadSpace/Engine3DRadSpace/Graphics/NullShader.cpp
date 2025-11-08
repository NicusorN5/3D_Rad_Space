#include "NullShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void* NullShader::GetHandle() const noexcept
{
	return nullptr;
}
IGraphicsDevice* NullShader::GetGraphicsDevice() const noexcept
{
	return nullptr;
}

void NullShader::SetData(unsigned index, const void *data, size_t dataSize)
{
	(void)index;
	(void)data;
	(void)dataSize;
}

void NullShader::SetTexture(unsigned index, ITexture2D *texture)
{
	(void)index;
	(void)texture;
}

void NullShader::SetTextures(std::span<ITexture2D*> textures)
{
	(void)textures;
}

void NullShader::SetSampler(unsigned index, ISamplerState *samplerState)
{
	(void)index;
	(void)samplerState;
}

void NullShader::SetShader()
{
}

std::vector<Reflection::IReflectedField*> NullShader::GetVariables() const
{
	return std::vector<Reflection::IReflectedField*>();
}

void NullShader::Set(const std::string& name, const void* data, size_t dataSize)
{
	(void)name;
	(void)data;
	(void)dataSize;
}

ShaderFeatureLevel NullShader::ShaGetFeatureLevel()
{
	return ShaderFeatureLevel::DX_V4;
}

std::string NullShader::GetEntryName()
{
	return "";
}

const char* NullShader::GetCompilationErrorsAndWarnings()
{
	return "";
}