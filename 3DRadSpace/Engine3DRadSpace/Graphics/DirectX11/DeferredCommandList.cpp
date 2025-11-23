#include "DeferredCommandList.hpp"
#include "GraphicsDevice.hpp"
#include "../Core/Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

DeferredCommandList::DeferredCommandList(GraphicsDevice* device) :
	GraphicsCommandList(device)
{
	HRESULT r = device->CreateDeferredContext(0, &_deferredContext);
	if (FAILED(r)) throw Exception("Failed to create deferred context!");
	_context = _deferredContext.Get();
}