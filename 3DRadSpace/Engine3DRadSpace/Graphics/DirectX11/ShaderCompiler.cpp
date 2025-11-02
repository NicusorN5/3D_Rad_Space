#include "ShaderCompiler.hpp"
#include "GraphicsDevice.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"
#include "DomainShader.hpp"
#include "GeometryShader.hpp"
#include "HullShader.hpp"
#include "ShaderBase.hpp"
#include "../../Core/Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

ShaderCompiler::ShaderCompiler(GraphicsDevice *device) :
    _device(device)
{
}

ShaderCompiler::CompileOutput ShaderCompiler::Compile(const ShaderDesc* desc)
{
    if (desc == nullptr) return std::make_pair<std::unique_ptr<IShader>, ShaderCompilationResult>(
        nullptr,
        ShaderCompilationResult
        {
            "No shader description provided.",
            false
        }
     );

    ShaderCompilationResult result;

    if (dynamic_cast<const ShaderDescFile*>(desc) != nullptr)
    {
        auto fileDesc = static_cast<const ShaderDescFile*>(desc);

        switch (fileDesc->Type)
        {
        case ShaderType::Vertex:
        {
            result = new DirectX11::VertexShader(
                _device,
                fileDesc->InputLayout,
                fileDesc->Path,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
			);
            break;
        }
        case ShaderType::Fragment:
        {
            result.Shader = new DirectX11::FragmentShader(
                _device,
                fileDesc->Path,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
            );
            break;
        }
        case ShaderType::Geometry:
        {
            result.Shader = new DirectX11::GeometryShader(
                _device,
                fileDesc->Path,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
			);
            break;
        }
        case ShaderType::Hull:
        {
            result.Shader = new DirectX11::HullShader(
                _device,
                fileDesc->Path,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
            );
            break;
        }
        case ShaderType::Domain:
        {
            
            result.Shader = new DirectX11::DomainShader(
                _device,
                fileDesc->Path,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
			);
            break;
        }
        default:
            return ShaderCompilationResult
            {
                nullptr,
                "Unsupported shader type.",
                false
            };
        }
    }
    else if (dynamic_cast<ShaderDescSource*>(desc) != nullptr)
    {
        case ShaderType::VertexShader:
        {
            result.Shader = new DirectX11::VertexShader(
                _device,
                fileDesc->InputLayout,
                fileDesc->SourceCode,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
            );
            break;
        }
        case ShaderType::FragmentShader:
        {
            result.Shader = new DirectX11::FragmentShader(
                _device,
                fileDesc->SourceCode,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
			);
            break;
        }
        case ShaderType::GeometryShader:
        {
            result.Shader = new DirectX11::GeometryShader(
                _device,
                fileDesc->SourceCode,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
            );
            break;
        }
        case ShaderType::HullShader:
        {
            result.Shader = new DirectX11::HullShader(
                _device,
                fileDesc->SourceCode,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
			);
            break;
        }
        case ShaderType::DomainShader:
        {
            result.Shader = new DirectX11::DomainShader(
                _device,
                fileDesc->SourceCode,
                fileDesc->EntryPoint.c_str(),
                fileDesc->FeatureLevel
            );
            break;
        }
        default:
            return ShaderCompilationResult
            {
                nullptr,
                "Unsupported shader type.",
                false
            };
    }
}

std::vector<ShaderCompiler::CompileOutput> ShaderCompiler::CompileEffect(std::span<ShaderDesc*> descs)
{
    for (ShaderDesc *desc : descs)
    {
        
    }
}