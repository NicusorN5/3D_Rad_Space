#include "Effect.hpp"

using namespace Engine3DRadSpace::Graphics;

Effect::Effect(
	IGraphicsDevice *device, 
	std::span<IShader*> shaders
) : 
	_device(device),
	_shaders()
{
	_shaders.assign(shaders.begin(), shaders.end());
}

int Effect::SetAll() const noexcept
{
	int r = 0;
	for (auto shader : _shaders)
	{
		if (shader != nullptr)
		{
			shader->SetShader();
			r++;
		}
	}
	return r;
}

bool Effect::Set(int index) const noexcept
{
	if (_shaders[index] != nullptr)
	{
		_shaders[index]->SetShader();
		return true;
	}
	return false;
}

void Effect::SetData(void* data, size_t size, int cbufferID, int shaderID)
{
	_shaders[shaderID]->SetData(cbufferID, data, size);
}

void Effect::SetData(void* data, size_t size, int cbufferID)
{
	for (auto shader : _shaders)
	{
		shader->SetData(cbufferID, data, size);
	}
}

void Effect::SetTexture(ITexture2D* texture, int idx) noexcept
{
	for (auto shader : _shaders)
	{
		shader->SetTexture(idx, texture);
	}
}

void Effect::SetTexture(ITexture2D* texture, int textureID, int shaderID) noexcept
{
	_shaders[shaderID]->SetTexture(textureID, texture);
}

void Effect::SetSampler(ISamplerState* sampler, int idx) noexcept
{
	for (auto shader : _shaders)
	{
		shader->SetSampler(idx, sampler);
	}
}

void Effect::SetSampler(ISamplerState* sampler, int samplerID, int shaderID) noexcept
{
	_shaders[shaderID]->SetSampler(samplerID, sampler);
}

IShader* Effect::operator[](size_t idx) const
{
	return _shaders.at(idx);
}