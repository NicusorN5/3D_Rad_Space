/// ------------------------------------------------------------------------------------------------
/// File:   Graphics/RasterizerState.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "RasterizerState.hpp"
#include "../Logging/Exception.hpp"
#include "../GraphicsDevice.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void RasterizerState::_debugInfo()
{
#ifdef USING_DX11
#ifdef DEBUG
	const char textureName[] = "RasterizerState::_rasterizerState";
	_rasterizerState->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);
#endif // DEBUG
#endif
}

RasterizerState::RasterizerState(
	GraphicsDevice* device,
	RasterizerFillMode filling, 
	RasterizerCullMode culling, 
	bool switchFrontBack, 
	int depthBias, 
	float depthBiasClamp, 
	float slopeScaleDepthBias, 
	bool depthClip,
	bool scissor,
	bool multisample,
	bool aaLine) 
{
#ifdef USING_DX11
	D3D11_RASTERIZER_DESC desc{};
	desc.FillMode = static_cast<D3D11_FILL_MODE>(filling); //TODO: prefer using a switch case
	desc.CullMode = static_cast<D3D11_CULL_MODE>(culling);
	desc.FrontCounterClockwise = switchFrontBack;
	desc.DepthBias = depthBias;
	desc.DepthBiasClamp = depthBiasClamp;
	desc.SlopeScaledDepthBias = slopeScaleDepthBias;
	desc.DepthClipEnable = depthClip;
	desc.ScissorEnable = scissor;
	desc.MultisampleEnable = multisample;
	desc.AntialiasedLineEnable = aaLine;

	HRESULT r = device->_device->CreateRasterizerState(&desc, _rasterizerState.ReleaseAndGetAddressOf());
	if (FAILED(r)) throw Exception("Failed to create a rasterizer state object");

#ifdef _DEBUG
	const char rasterizerStateName[] = "RasterizerState::_rasterizerState";
	_rasterizerState->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(rasterizerStateName) - 1, rasterizerStateName);
#endif
	_debugInfo();
#endif
}

RasterizerState::RasterizerState(GraphicsDevice* device, std::monostate cpy)
{
	(void)cpy; //unused argument
#ifdef USING_DX11
	device->_context->RSGetState(&_rasterizerState);
#endif
}

void* RasterizerState::GetHandle() const noexcept
{
	return static_cast<void*>(_rasterizerState.Get());
}

RasterizerState RasterizerState::CullNone(GraphicsDevice *device)
{
	// https://github.com/microsoft/DirectXTK/wiki/CommonStates
	return RasterizerState(device, 
		RasterizerFillMode::Solid, 
		RasterizerCullMode::None,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState RasterizerState::CullClockwise(GraphicsDevice *device)
{
	return RasterizerState(device,
		RasterizerFillMode::Solid,
		RasterizerCullMode::CullFront,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState RasterizerState::CullCounterClockwise(GraphicsDevice *device)
{
	return RasterizerState(device,
		RasterizerFillMode::Solid,
		RasterizerCullMode::CullBack,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState RasterizerState::Wireframe(GraphicsDevice *device)
{
	return RasterizerState(device,
		RasterizerFillMode::Wireframe,
		RasterizerCullMode::None,
		false, //FrontCounterClockwise 
		0, // D3D11_DEFAULT_DEPTH_BIAS
		0.0f, // D3D11_DEFAULT_DEPTH_BIAS_CLAMP
		0.0f, //D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS
		true, //DepthClipEnable 
		false, //ScissorEnable 
		true, //MultisampleEnable 
		false //AntialiasedLineEnable 
	);
}

RasterizerState RasterizerState::GetCurrentRasterizerState(GraphicsDevice* device)
{
	return RasterizerState(device, std::monostate{});
}
