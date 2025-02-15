/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/Rendering/PostProcessCollection.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
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