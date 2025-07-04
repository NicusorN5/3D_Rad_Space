#include "DepthStencilState.hpp"
#include "../Core/Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

void DepthStencilState::_debugInfo()
{
#ifdef USING_DX11
#ifdef _DEBUG
    const char stateName[] = "DepthStencilState::_state";
    _state->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(stateName) - 1, stateName);
#endif
#endif
}

DepthStencilState::DepthStencilState(GraphicsDevice *device)
{
#ifdef USING_DX11
    CD3D11_DEPTH_STENCIL_DESC dsDesc(D3D11_DEFAULT);

    HRESULT r = device->_device->CreateDepthStencilState(&dsDesc, _state.GetAddressOf());
    if (FAILED(r)) throw Exception("Failed to create a depth stencil state");
#endif
}

DepthStencilState::DepthStencilState(GraphicsDevice* device, std::monostate cpy)
{
#ifdef USING_DX11
    device->_context->OMGetDepthStencilState(&_state, &_stencilRef);
#endif
}

DepthStencilState::DepthStencilState(GraphicsDevice *device, bool EnableDepth, DepthWriteMask Mask, ComparisonFunction Function, bool EnableStencil, 
    uint8_t ReadMask, uint8_t WriteMask, FaceOperation FrontFace, FaceOperation BackFace)
{
#ifdef USING_DX11
    D3D11_DEPTH_STENCIL_DESC dsDesc;
    dsDesc.DepthEnable = EnableDepth;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(WriteMask); //REFACTORING-NOTE: don't use initialization, may prefer a switch-case.
    dsDesc.DepthFunc = D3D11_COMPARISON_FUNC(Function);

    dsDesc.StencilEnable = EnableStencil;
    dsDesc.StencilReadMask = ReadMask;
    dsDesc.StencilWriteMask = WriteMask;

    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP(FrontFace.StencilFail);
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP(FrontFace.DepthFail);
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP(FrontFace.PassOp);
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC(FrontFace.Function);

    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP(BackFace.StencilFail);
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP(BackFace.DepthFail);
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP(BackFace.PassOp);
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC(BackFace.Function);

    HRESULT r = device->_device->CreateDepthStencilState(&dsDesc, _state.GetAddressOf());
    if (FAILED(r)) throw Exception("Failed to create a depth stencil state");
#endif
}

unsigned int DepthStencilState::StencilRef() const noexcept
{
    return _stencilRef;
}

void* DepthStencilState::GetHandle() const noexcept
{
    return static_cast<void*>(this->_state.Get());
}

DepthStencilState DepthStencilState::DepthDefault(GraphicsDevice* device)
{
    // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_depth_stencil_desc
    return DepthStencilState(
        device,
        true, // EnableDepth
        DepthWriteMask::All, // Mask
        ComparisonFunction::LessEqual, // Function
        false, // EnableStencil
        1, // ReadMask D3D11_DEFAULT_STENCIL_READ_MASK
        1, // WriteMask D3D11_DEFAULT_STENCIL_WRITE_MASK
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        },
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        }
    );
}

DepthStencilState DepthStencilState::DepthNone(GraphicsDevice *device)
{
    //https://github.com/microsoft/DirectXTK/wiki/CommonStates
    return DepthStencilState(
        device,
        false, // EnableDepth
        DepthWriteMask::All, // Mask
        ComparisonFunction::LessEqual, // Function
        false, // EnableStencil
        0xFF, // ReadMaskD3D11_DEFAULT_STENCIL_READ_MASK
        0, // WriteMask D3D11_DEPTH_WRITE_MASK_ZERO
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        },
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        }
    );
}

DepthStencilState DepthStencilState::DepthRead(GraphicsDevice *device)
{
    return DepthStencilState(
        device,
        true, // EnableDepth
        DepthWriteMask::All, // Mask
        ComparisonFunction::LessEqual, // Function
        false, // EnableStencil
        0xFF, // ReadMaskD3D11_DEFAULT_STENCIL_READ_MASK
        0, // WriteMask D3D11_DEPTH_WRITE_MASK_ZERO
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        },
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        }
    );
}

DepthStencilState DepthStencilState::DepthReverseZ(GraphicsDevice *device)
{
    return DepthStencilState(
        device,
        true, // EnableDepth
        DepthWriteMask::All, // Mask
        ComparisonFunction::GreaterEqual, // Function
        false, // EnableStencil
        0xFF, // ReadMaskD3D11_DEFAULT_STENCIL_READ_MASK
        0xFF, // WriteMask D3D11_DEFAULT_STENCIL_WRITE_MASK
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        },
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        }
    );
}

DepthStencilState DepthStencilState::DepthReadReverseZ(GraphicsDevice *device)
{
    return DepthStencilState(
        device,
        true, // EnableDepth
        DepthWriteMask::All, // Mask
        ComparisonFunction::GreaterEqual, // Function
        false, // EnableStencil
        0xFF, // ReadMaskD3D11_DEFAULT_STENCIL_READ_MASK
        0, // WriteMask D3D11_DEPTH_WRITE_MASK_ZERO
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        },
        FaceOperation{
            .StencilFail = StencilOperation::Keep,
            .DepthFail = StencilOperation::Keep,
            .PassOp = StencilOperation::Keep,
            .Function = ComparisonFunction::Always,
        }
    );
}

