#pragma once
#include "GraphicsCommandList.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class DeferredCommandList: public GraphicsCommandList
	{
		std::unique_ptr<ID3D11DeviceContext> _deferredContext;
	public:
		DeferredCommandList(GraphicsDevice* device);

		~DeferredCommandList() override = default;
	};
}