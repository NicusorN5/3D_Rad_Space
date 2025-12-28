#pragma once
#include "IVertexShader.hpp"
#include "IVertexShader.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

E3DRSP_IReflectedField** E3DRSP_IVertexShader_GetInputLayout(E3DRSP_IVertexShader vertexShader, size_t* outSize)
{
	if (outSize == nullptr)
	{
		return nullptr;
	}

	auto layout = reinterpret_cast<IVertexShader*>(vertexShader)->GetInputLayout();
	*outSize = layout.size();

	auto cLayout = new E3DRSP_IReflectedField* [layout.size()];
	for (size_t i = 0; i < layout.size(); i++)
	{
		cLayout[i] = reinterpret_cast<E3DRSP_IReflectedField*>(layout[i]);
	}
	return cLayout;
}

E3DRSP_GRAPHICS_EXPORT void E3DRSP_IVertexShader_Destroy(E3DRSP_IVertexShader vertexShader)
{
	delete reinterpret_cast<IVertexShader*>(vertexShader);
}