namespace Engine3DRadSpace.Graphics;

public interface IShader : IPtrWrapper
{
	public void SetData(uint index, IntPtr data, ulong dataSize);
	public void SetTexture(uint index, ITexture2D texture);
	public void SetTextures(Span<ITexture2D> textures);
	public void SetSampler(uint index, ISamplerState samplerState);
	public void SetShader();
	public Reflection.IReflectedField[] GetVariables();
	public string EntryName { get; }
	public string CompilationErrorsAndWarnings { get; }
}
