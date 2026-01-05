#include "Effect.hpp"
#include "Effect.h"

using namespace Engine3DRadSpace;
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

E3DRSP_Effect E3DRSP_Effect_Create(E3DRSP_IGraphicsDevice device, E3DRSP_IShader* shaders, size_t numShaders)
{
	return static_cast<E3DRSP_Effect>(
		new Effect(
			reinterpret_cast<IGraphicsDevice*>(device), 
			std::span<IShader*>(reinterpret_cast<IShader**>(shaders), numShaders))
	);
}

int E3DRSP_Effect_SetAll(E3DRSP_Effect effect)
{
	return reinterpret_cast<Effect*>(effect)->SetAll();
}

bool E3DRSP_Effect_Set(E3DRSP_Effect effect, int index)
{
	return reinterpret_cast<Effect*>(effect)->Set(index);
}

void E3DRSP_Effect_SetData(E3DRSP_Effect effect, void* data, size_t size, int cbufferID, int shaderID)
{
	return reinterpret_cast<Effect*>(effect)->SetData(data, size, cbufferID, shaderID);
}

void E3DRSP_Effect_SetData2(E3DRSP_Effect effect, void* data, size_t size, int cbufferID)
{
	reinterpret_cast<Effect*>(effect)->SetData(data, size, cbufferID);
}

void E3DRSP_Effect_SetTexture(E3DRSP_Effect effect, E3DRSP_ITexture2D texture, int idx)
{
	reinterpret_cast<Effect*>(effect)->SetTexture(reinterpret_cast<ITexture2D*>(texture), idx);
}

void E3DRSP_Effect_SetTexture2(E3DRSP_Effect effect, E3DRSP_ITexture2D texture, int textureID, int shaderID)
{
	reinterpret_cast<Effect*>(effect)->SetTexture(reinterpret_cast<ITexture2D*>(texture), textureID, shaderID);
}

void E3DRSP_Effect_SetSampler(E3DRSP_Effect effect, E3DRSP_ISamplerState sampler, int idx)
{
	reinterpret_cast<Effect*>(effect)->SetSampler(reinterpret_cast<ISamplerState*>(sampler), idx);
}

void E3DRSP_Effect_SetSampler2(E3DRSP_Effect effect, E3DRSP_ISamplerState sampler, int samplerID, int shaderID)
{
	reinterpret_cast<Effect*>(effect)->SetSampler(reinterpret_cast<ISamplerState*>(sampler), samplerID, shaderID);
}

E3DRSP_IShader* E3DRSP_Effect_GetShader(E3DRSP_Effect effect, size_t idx)
{
	auto shader = reinterpret_cast<Effect*>(effect)->operator[](idx);
	return reinterpret_cast<E3DRSP_IShader*>(shader);
}

void E3DRSP_Effect_Destroy(E3DRSP_Effect effect)
{
	assert(effect != nullptr);
	delete reinterpret_cast<Effect*>(effect);
}