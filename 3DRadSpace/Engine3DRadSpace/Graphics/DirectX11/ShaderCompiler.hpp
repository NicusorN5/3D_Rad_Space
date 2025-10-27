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

        [[nodiscard]] std::pair<std::unique_ptr<Effect>, ShaderCompilationResult> Compile(const ShaderDesc* desc) override;
        [[nodiscard]] std::vector<std::pair<std::unique_ptr<Effect>, ShaderCompilationResult>> CompileEffect(const ShaderDesc* const* descs) override;

        ~ShaderCompiler() override = default;
    };
}