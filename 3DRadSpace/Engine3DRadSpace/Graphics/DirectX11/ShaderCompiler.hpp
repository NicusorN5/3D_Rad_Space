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

        [[nodiscard]] CompileOutput Compile(const ShaderDesc* desc) override;
        [[nodiscard]] std::vector<CompileOutput> CompileEffect(std::span<ShaderDesc*> descs) override;

        ~ShaderCompiler() override = default;
    };
}