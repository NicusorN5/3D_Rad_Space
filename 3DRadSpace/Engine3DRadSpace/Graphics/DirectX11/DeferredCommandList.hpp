#pragma once
#include "GraphicsCommandList.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class E3DRSP_GRAPHICS_DX11_EXPORT DeferredCommandList: public GraphicsCommandList
	{
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deferredContext;
	public:
		DeferredCommandList(GraphicsDevice* device);

		~DeferredCommandList() override = default;
	};
}