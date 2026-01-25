namespace Engine3DRadSpace.Graphics;

public interface IShaderCompiler : IPtrWrapper
{
    public CompileOutput CompileShader(ShaderDesc shaderDescription);
    public EffectCompileOutput CompileEffect(ShaderDesc[] descs);
}
