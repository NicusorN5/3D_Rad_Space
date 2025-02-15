/// ------------------------------------------------------------------------------------------------
/// File:   Content/ShaderManager.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "ShaderManager.hpp"

using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics::Shaders;

std::unordered_map<size_t, std::shared_ptr<Effect>> ShaderManager::_shaders;

void ShaderManager::ReleaseAll()
{
	for(auto &[id, shader] : _shaders)
	{
		shader.reset();
	}
}
