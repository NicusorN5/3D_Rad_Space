#pragma once
#include "../ISamplerState.hpp"
#include "GraphicsDevice.hpp"
#include "../TextureFilter.hpp"
#include "../TextureAddressMode.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class E3DRSP_GRAPHICS_EXPORT SamplerState : public ISamplerState
	{
		GraphicsDevice* _device;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplerState;
		void _debugInfo();
	public:
		SamplerState(GraphicsDevice *device);
		SamplerState(GraphicsDevice* device, TextureFilter Filter, TextureAddressMode AddressU, TextureAddressMode AddressV, TextureAddressMode AddressW,
			float MipLODBias, unsigned MaxAnisotropy, ComparisonFunction ComparisionFunction, Math::Color BorderColor, float MinLOD, float MaxLOD);

		SamplerState(SamplerState &) = delete;
		SamplerState(SamplerState &&) noexcept = default;

		SamplerState& operator=(SamplerState &) = delete;
		SamplerState& operator=(SamplerState &&) noexcept = default;

		static SamplerState LinearClamp(GraphicsDevice *device);
		static SamplerState LinearWrap(GraphicsDevice *device);

		static SamplerState PointClamp(GraphicsDevice *device);
		static SamplerState PointWrap(GraphicsDevice *device);

		static SamplerState AnisotropicClamp(GraphicsDevice *device);
		static SamplerState AnisotropicWrap(GraphicsDevice *device);

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~SamplerState() = default;

		friend class IVertexShader;
		friend class IFragmentShader;
		friend class IHullShader;
		friend class IDomainShader;
		friend class IGeometryShader;
	};
}

