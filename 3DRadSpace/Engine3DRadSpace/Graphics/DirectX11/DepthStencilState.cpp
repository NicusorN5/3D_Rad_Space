#include "DepthStencilState.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

void DepthStencilState::_debugInfo()
{
#ifdef _DEBUG
    const char stateName[] = "DepthStencilState::_state";
    _state->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(stateName) - 1, stateName);
#endif
}

DepthStencilState::DepthStencilState(GraphicsDevice *device) :
    _device(device),
    _stencilRef(0)
{
    CD3D11_DEPTH_STENCIL_DESC dsDesc(D3D11_DEFAULT);

    HRESULT r = device->_device->CreateDepthStencilState(&dsDesc, _state.GetAddressOf());
    if (FAILED(r)) throw Exception("Failed to create a depth stencil state");
}

DepthStencilState::DepthStencilState(GraphicsDevice* device, std::monostate cpy):
    _device(device)
{
    device->_context->OMGetDepthStencilState(&_state, &_stencilRef);
}

DepthStencilState::DepthStencilState(
    GraphicsDevice *device, 
    bool EnableDepth,
    DepthWriteMask Mask,
    ComparisonFunction Function,
    bool EnableStencil, 
    uint8_t ReadMask,
    uint8_t WriteMask, 
    FaceOperation FrontFace, 
    FaceOperation BackFace
): _device(device),
   _stencilRef(0)
{
    D3D11_DEPTH_STENCIL_DESC dsDesc;
    dsDesc.DepthEnable = EnableDepth;
    dsDesc.DepthWriteMask = static_cast<D3D11_DEPTH_WRITE_MASK>(Mask); //REFACTORING-NOTE: don't use initialization, may prefer a switch-case.
    dsDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(Function);

    dsDesc.StencilEnable = EnableStencil;
    dsDesc.StencilReadMask = ReadMask;
    dsDesc.StencilWriteMask = WriteMask;

    dsDesc.FrontFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(FrontFace.StencilFail);
    dsDesc.FrontFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(FrontFace.DepthFail);
    dsDesc.FrontFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(FrontFace.PassOp);
    dsDesc.FrontFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(FrontFace.Function);

    dsDesc.BackFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(BackFace.StencilFail);
    dsDesc.BackFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(BackFace.DepthFail);
    dsDesc.BackFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(BackFace.PassOp);
    dsDesc.BackFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(BackFace.Function);

    HRESULT r = device->_device->CreateDepthStencilState(&dsDesc, _state.GetAddressOf());
    if (FAILED(r)) throw Exception("Failed to create a depth stencil state");
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

IGraphicsDevice* DepthStencilState::GetGraphicsDevice() const noexcept
{
    return _device;
}

DepthStencilState DepthStencilState::GetCurrent(GraphicsDevice* device)
{
    return DepthStencilState(device, std::monostate{});
}