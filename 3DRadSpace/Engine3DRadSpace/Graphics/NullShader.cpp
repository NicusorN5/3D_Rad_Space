#include "NullShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void* NullShader::GetHandle() const noexcept //override
{
	return nullptr;
}
IGraphicsDevice* NullShader::GetGraphicsDevice() const noexcept //override
{
	return nullptr;
}

void NullShader::SetData(unsigned index, const void *data, unsigned dataSize) //override
{
	(void)index;
	(void)data;
	(void)dataSize;
}

void NullShader::SetTexture(unsigned index, ITexture2D *texture) //override
{
	(void)index;
	(void)texture;
}

void NullShader::SetSampler(unsigned index, ISamplerState *samplerState) //override
{
	(void)index;
	(void)samplerState;
}