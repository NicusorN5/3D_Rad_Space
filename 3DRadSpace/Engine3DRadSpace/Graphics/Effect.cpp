#include "Effect.hpp"

using namespace Engine3DRadSpace::Graphics;

Effect::Effect(
	IGraphicsDevice *device, 
	std::span<IShader*> shaders
) : 
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
			_device->SetShader(shader);
			r++;
		}
	}
	return r;
}

bool Effect::Set(int index) const noexcept
{
	bool r = false;
	if (_shaders[index] != nullptr)
	{

	}
}

void Effect::SetTexture(ITexture2D* texture, int idx) noexcept
{
	for (auto shader : _shaders)
	{
		shader->SetTexture(idx, texture);
	}
}

void Effect::SetSampler(ISamplerState* sampler, int idx) noexcept
{
	for (auto shader : _shaders)
	{
		shader->SetSampler(idx, sampler);
	}
}