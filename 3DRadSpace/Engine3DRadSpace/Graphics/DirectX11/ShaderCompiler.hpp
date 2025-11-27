#pragma once
#include "../IShaderCompiler.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
    class GraphicsDevice;

    class E3DRSP_GRAPHICS_DX11_EXPORT ShaderCompiler final: public IShaderCompiler
    {
        GraphicsDevice* _device;

        std::string shaderID_file(const ShaderDescFile* fileDesc);
        std::string shaderID(const ShaderDesc* fileDesc);
    public:
        ShaderCompiler(GraphicsDevice* device);

        ShaderCompiler(const ShaderCompiler&) = delete;
        ShaderCompiler(ShaderCompiler&&) = delete;

        ShaderCompiler& operator=(const ShaderCompiler&) = delete;
        ShaderCompiler& operator=(ShaderCompiler&&) = delete;

        [[nodiscard]] CompileOutput Compile(const ShaderDesc* desc) override;
        [[nodiscard]] EffectCompileOutput CompileEffect(std::span<ShaderDesc*> descs) override;

        ~ShaderCompiler() override = default;
    };
}