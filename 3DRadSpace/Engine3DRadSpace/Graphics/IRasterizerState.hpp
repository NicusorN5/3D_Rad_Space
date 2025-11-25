#pragma once
#include "IGPUResource.hpp"
#include "RasterizerFillMode.hpp"
#include "RasterizerCullMode.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the rasterizer state.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IRasterizerState : public IGPUResource
	{
	protected:
		IRasterizerState() = default;
	public:
		virtual std::unique_ptr<IRasterizerState> GetCurrentRasterizerState(IGraphicsDevice* device) = 0;

		~IRasterizerState() override = default;
	};
}