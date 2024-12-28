#include "PostProcessCollection.hpp"
#include "PostProcessCollection.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessCollection::PostProcessCollection(GraphicsDevice* device):
	_device(device)
{
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
		effect->Draw();
	}
}
