#include "IShader.hpp"
#include "IShader.h"
#include "../Reflection/IReflectedField.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

void E3DRSP_IShader_SetData(E3DRSP_IShader shader, unsigned index, const void* data, size_t dataSize)
{
	reinterpret_cast<IShader*>(shader)->SetData(index, data, dataSize);
}

void E3DRSP_IShader_SetTexture(E3DRSP_IShader shader, unsigned index, E3DRSP_ITexture2D texture)
{
	reinterpret_cast<IShader*>(shader)->SetTexture(index, reinterpret_cast<ITexture2D*>(texture));
}

void E3DRSP_IShader_SetTextures(E3DRSP_IShader shader, E3DRSP_ITexture2D* textures, size_t numTextures)
{
	std::vector<ITexture2D*> texVec;
	texVec.reserve(numTextures);
	for (size_t i = 0; i < numTextures; i++)
	{
		texVec.push_back(reinterpret_cast<ITexture2D*>(textures[i]));
	}
	reinterpret_cast<IShader*>(shader)->SetTextures(texVec);
}

void E3DRSP_IShader_SetSampler(E3DRSP_IShader shader, unsigned index, E3DRSP_ISamplerState samplerState)
{
	reinterpret_cast<IShader*>(shader)->SetSampler(index, reinterpret_cast<ISamplerState*>(samplerState));
}

void E3DRSP_IShader_SetShader(E3DRSP_IShader shader)
{
	reinterpret_cast<IShader*>(shader)->SetShader();
}

E3DRSP_IReflectedField* E3DRSP_IShader_GetVariables(E3DRSP_IShader shader, size_t* outSize)
{
	auto vars = reinterpret_cast<IShader*>(shader)->GetVariables();
	size_t size = vars.size();
	*outSize = size;
	E3DRSP_IReflectedField* result = new E3DRSP_IReflectedField[size];

	for (size_t i = 0; i < size; i++)
	{
		result[i] = reinterpret_cast<E3DRSP_IReflectedField>(vars[i]);
	}
	return result;
}

void E3DRSP_IShader_Set(E3DRSP_IShader shader, const char* name, const void* data, size_t dataSize)
{
	reinterpret_cast<IShader*>(shader)->Set(std::string(name), data, dataSize);
}

const char* E3DRSP_IShader_GetEntryName(E3DRSP_IShader shader)
{
	return reinterpret_cast<IShader*>(shader)->GetEntryName().data();
}

const char* E3DRSP_IShader_GetCompilationErrorsAndWarnings(E3DRSP_IShader shader)
{
	return reinterpret_cast<IShader*>(shader)->GetCompilationErrorsAndWarnings();
}

void E3DRSP_IShader_Destroy(E3DRSP_IShader shader)
{
	delete reinterpret_cast<IShader*>(shader);
}