#include "PostProcessCollection.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessCollection::PostProcessCollection(GraphicsDevice* device):
	_device(device)
{
	//TODO - Get the backbuffer and depth buffer format from the device, don't hardcode them.
	_backbuffer_cpy = std::make_unique<Texture2D>(device, device->Resolution().X, device->Resolution().Y, PixelFormat::R16G16B16A16_Float);
	_depthbuffer_cpy = std::make_unique<Texture2D>(std::move(device->GetDepthBuffer().CloneDepthTexture()));
}

size_t PostProcessCollection::Length() const noexcept
{
	return _effects.size();
}

void PostProcessCollection::ApplyAll()
{
	for(auto& effect : _effects)
	{
		if(!effect->Enabled) continue;
		
		_device->UnbindRenderTargetAndDepth();
		Texture2D::Copy(_backbuffer_cpy.get(), _device->GetBackBufferTexture());
		Texture2D::Copy(_depthbuffer_cpy.get(), _device->GetDepthBuffer().GetDepthTexture());

		effect->Apply();
		_device->SetRenderTargetAndDisableDepth(nullptr);
		effect->Draw();
	}
}

void PostProcessCollection::EnableAll()
{
	for(auto& effect : _effects)
	{
		effect->Enabled = false;
	}
}

void PostProcessCollection::DisableAll()
{
	for(auto& effect : _effects)
	{
		effect->Enabled = false;
	}
}