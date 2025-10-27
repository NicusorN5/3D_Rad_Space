#pragma once
#include "../ISamplerState.hpp"
#include "GraphicsDevice.hpp"
#include "../TextureFilter.hpp"
#include "../TextureAddressMode.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class E3DRSP_GRAPHICS_EXPORT SamplerState : public ISamplerState
	{
	public:
		SamplerState(GraphicsDevice* device);
		SamplerState(GraphicsDevice* device, TextureFilter Filter, TextureAddressMode AddressU, TextureAddressMode AddressV, TextureAddressMode AddressW,
			float MipLODBias, unsigned MaxAnisotropy, ComparisonFunction ComparisionFunction, Math::Color BorderColor, float MinLOD, float MaxLOD);

		SamplerState(SamplerState&) = delete;
		SamplerState(SamplerState&&) noexcept = default;

		SamplerState& operator=(SamplerState&) = delete;
		SamplerState& operator=(SamplerState&&) noexcept = default;

		static SamplerState LinearClamp(GraphicsDevice* device);
		static SamplerState LinearWrap(GraphicsDevice* device);

		static SamplerState PointClamp(GraphicsDevice* device);
		static SamplerState PointWrap(GraphicsDevice* device);

		static SamplerState AnisotropicClamp(GraphicsDevice* device);
		static SamplerState AnisotropicWrap(GraphicsDevice* device);

		const void* GetHandle() const noexcept override;

		~SamplerState() override = default;
	};
}