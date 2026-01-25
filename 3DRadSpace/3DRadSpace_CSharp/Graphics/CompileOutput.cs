using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

[StructLayout(LayoutKind.Sequential)]
public struct CompileOutput
{
	public IntPtr Shader;
	public ShaderCompilationResult Result;

	public CompileOutput(IntPtr shader, ShaderCompilationResult r)
	{
		Shader = shader;
		Result = r;
	}
}