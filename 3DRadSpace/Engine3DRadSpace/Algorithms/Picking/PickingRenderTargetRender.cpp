#include "PickingRenderTargetRender.hpp"
#include "..\..\Content\ShaderManager.hpp"

using namespace Engine3DRadSpace::Algorithms::Picking;

PickingRenderTargetRender::PickingRenderTargetRender(GraphicsDevice* device) :
	IRenderer(device),
	_renderTarget(std::make_unique<Graphics::RenderTarget>(device, Graphics::PixelFormat::R32_UnsignedInt)),
	_shader(Content::ShaderManager::LoadShader<PickingShader>(device))
{
}

void PickingRenderTargetRender::Begin()
{
	if (_isDrawing)
	{
		_device->SetRenderTargetAndDepth(_renderTarget.get(), nullptr);
		_device->ClearRenderTarget(_renderTarget.get());

		bool r = _shader->SetFragment();
		if(!r) throw std::exception("Failed to set fragment shader.");

		_isDrawing = false;
	}
	else throw std::exception("Begin() already called.");
}

void PickingRenderTargetRender::End()
{
	_isDrawing = false;
	_device->SetRenderTargetAndDepth(nullptr, nullptr);
}

std::optional<unsigned> PickingRenderTargetRender::Pick(const Math::Point& mouseCoords)
{
	auto&& [buffer, size] = _renderTarget->BeginRead();
	unsigned ID = *(static_cast<int*>(buffer) + (mouseCoords.Y * _renderTarget->Width()) + mouseCoords.X);
	_renderTarget->EndRead();

	return ID + 1;
}