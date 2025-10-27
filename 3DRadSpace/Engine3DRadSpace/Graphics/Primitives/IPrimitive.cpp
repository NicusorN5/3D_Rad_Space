#include "IPrimitive.hpp"
#include "../Shaders/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;

IPrimitive::IPrimitive(IGraphicsDevice* device) :
	_device(device)
{
	_shader = ShaderManager::LoadShader<BlankShader>(device);
}

Math::Matrix4x4 IPrimitive::_mvp() const noexcept
{
	return Transform * View * Projection;
}
