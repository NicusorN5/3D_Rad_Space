using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics
{
	[StructLayout(LayoutKind.Sequential)]
	public struct EffectCompileOutput
    {
		public IntPtr Effect;
		public ShaderCompilationResult Result;

		public EffectCompileOutput(IntPtr effect, ShaderCompilationResult r)
		{
			Effect = effect;
			Result = r;
		}
	}
}