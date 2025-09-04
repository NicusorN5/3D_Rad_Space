#pragma once
#include "GPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IRasterizerState : GPUResource
	{
	protected:
		IRasterizerState() = default;
	public:
		RasterizerState(IRasterizerState &) = delete;
		RasterizerState(IRasterizerState &&state) noexcept = default;

		RasterizerState &operator =(IRasterizerState &) = delete;
		RasterizerState &operator =(IRasterizerState &&state) noexcept = default;

		~IRasterizerState() = default;
	};
}