#pragma once
#include "../IShaderCompiler.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
    class GraphicsDevice;

    class E3DRSP_GRAPHICS_EXPORT ShaderCompiler : public IShaderCompiler
    {
        GraphicsDevice* _device;
    public:
        ShaderCompiler(GraphicsDevice* device);

        ShaderCompiler(const ShaderCompiler&) = delete;
        ShaderCompiler(ShaderCompiler&&) = delete;

        ShaderCompiler& operator=(const ShaderCompiler&) = delete;
        ShaderCompiler& operator=(ShaderCompiler&&) = delete;

        ShaderCompilationResult CompileFile(
			const std::filesystem::path& path, 
			const std::string& entryPoint,
			ShaderType type
		) override;
		
        ShaderCompilationResult Compile(
			const std::string& src,
			const std::string& entryPoint,
			ShaderType type
		) override;

        ~ShaderCompiler() override = default;
    };
}