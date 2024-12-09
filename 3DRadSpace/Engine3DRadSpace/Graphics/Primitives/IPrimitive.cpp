#include "IPrimitive.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;

IPrimitive::IPrimitive(GraphicsDevice* device) :
	_device(device)
{

}

Math::Matrix4x4 IPrimitive::_mvp() const noexcept
{
	return Transform * View* Projection;
}
