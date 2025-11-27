#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a sampler state for texture sampling.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ISamplerState : public IGPUResource	
	{
	public:
		virtual ~ISamplerState() override = default;
	};
}	