#include "PostProcessCollection.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessCollection::PostProcessCollection(GraphicsDevice* device):
	_device(device)
{
	_effectRT = std::make_unique<RenderTarget>(device);
}

size_t PostProcessCollection::Length() const noexcept
{
	return _effects.size();
}

void PostProcessCollection::ApplyAll()
{
	for(auto& effect : _effects)
	{
		_device->SetRenderTargetAndDisableDepth(_effectRT.get());
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