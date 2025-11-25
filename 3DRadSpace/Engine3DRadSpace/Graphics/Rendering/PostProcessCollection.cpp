#include "PostProcessCollection.hpp"
#include "../IDepthStencilBuffer.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessCollection::PostProcessCollection(IGraphicsDevice* device):
	_device(device)
{
	//TODO - Get the backbuffer and depth buffer format from the device, don't hardcode them.
	_backbuffer_cpy = device->CreateTexture2D(
		nullptr,
		device->Resolution().X,
		device->Resolution().Y,
		PixelFormat::R16G16B16A16_Float,
		BufferUsage::ReadOnlyGPU_WriteOnlyCPU
	);

	_depthbuffer_cpy = device->GetDepthBuffer().CloneDepthTexture();
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
		
		auto cmd = _device->ImmediateContext();

		cmd->UnbindRenderTargetAndDepth();

		cmd->Copy(_backbuffer_cpy.get(), _device->GetBackBufferTexture());
		cmd->Copy(_depthbuffer_cpy.get(), _device->GetDepthBuffer().GetDepthTexture());

		effect->Apply();
		cmd->SetRenderTargetAndDisableDepth(nullptr);
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