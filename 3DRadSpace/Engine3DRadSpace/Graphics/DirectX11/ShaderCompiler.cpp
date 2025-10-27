#include "ShaderCompiler.hpp"
#include "GraphicsDevice.hpp"
#include "IVertexShader.hpp"
#include "IFragmentShader.hpp"
#include "IDomainShader.hpp"
#include "IGeometryShader.hpp"
#include "IHullShader.hpp"
#include "IShader.hpp"
#include "../../Core/Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

ShaderCompiler::ShaderCompiler(GraphicsDevice *device) :
    _device(device)
{
}

ShaderCompilationResult ShaderCompiler::Compile(const ShaderDesc* desc)
{
    if (desc == nullptr) return std::make_pair< ShaderCompilationResult
    {
        "No shader description provided.",
        false
    };

	ShaderCompilationResult result;

    if (dynamic_cast<ShaderDescFile*>(desc) != nullptr)
    {
		auto fileDesc = static_cast<const ShaderDescFile*>(desc);

        switch (fileDesc->Type)
        {
            case ShaderType::VertexShader:
            {
                // Compile vertex shader from file
                break;
            }
            case ShaderType::FragmentShader:
            {
                result.Shader = 
                break;
            }
            case ShaderType::GeometryShader:
            {
                // Compile geometry shader from file
                break;
            }
            case ShaderType::HullShader:
            {
                // Compile hull shader from file
                break;
            }
            case ShaderType::DomainShader:
            {
                // Compile domain shader from file
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
    }
}

std::pair<Effect*, std::vector<ShaderCompilationResult>> ShaderCompiler::CompileEffect(const ShaderDesc* const* descs)
{

}