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

template<typename FnShaderCtor, typename ...Args> 
ShaderCompilationResult _dx11_compile_shader(FnShaderCtor ctor, Args&& args...)
{

}

ShaderCompilationResult ShaderCompiler::CompileFile(
    const std::filesystem::path& path, 
    const std::string& entryPoint,
    ShaderType type
)
{

}
		
ShaderCompilationResult ShaderCompiler::Compile(
    const std::string& src,
    const std::string& entryPoint,
    ShaderType type
)
{
    ShaderCompilationResult result;
    result.Shader = nullptr;
    result.Succeded = true;
    IShader* ptr;

    auto compile = [=]<typename ShaderType>(ShaderCompilationResult &result) -> void
    {
        IShader* ptr;
        try
        {
            ptr = new ShaderType(_device, src, entryPoint.c_str());
            result.Log = ptr->GetCompilationErrorsAndWarnings();
        }
        catch(const Exception& e)
        {
            result.Succeded = false;
            result.Log = e.What();
        }
    };

    switch(type)
    {
        case ShaderType::Fragment:
            compile<IFragmentShader>(result);
            break;
        case ShaderType::Domain:
            compile<IDomainShader>(result);
            break;
        case ShaderType::Geometry:
            compile<IGeometryShader>(result);
            break;
        case ShaderType::Hull:
            compile<IHullShader>(result);
            break;
        default:
            result.Log = "Unsupported shader type.";
            break;
    }

    return result;
}