/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Primitives/IPrimitive.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "IPrimitive.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;

IPrimitive::IPrimitive(GraphicsDevice* device) :
	_device(device)
{
	_shader = ShaderManager::LoadShader<BlankShader>(device);
}

Math::Matrix4x4 IPrimitive::_mvp() const noexcept
{
	return Transform * View * Projection;
}
