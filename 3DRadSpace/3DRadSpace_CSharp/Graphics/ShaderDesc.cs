using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class ShaderDesc : NatPtrWrapper
{
	[DllImport("3DRadSpace.Graphics.dll", EntryPoint = "E3DRSP_ShaderDesc_Destroy")]
	extern static void _destroy(IntPtr desc);

	[DllImport("3DRadSpace.Graphics.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_ShaderDesc_CreateFromFile")]
	extern static IntPtr _createFile(string path, string entry, ShaderType type, ShaderFeatureLevel featureLevel);

	[DllImport("3DRadSpace.Graphics.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_ShaderDesc_CreateFromSource")]
	extern static IntPtr _createSrc(string src, string entry, ShaderType type, ShaderFeatureLevel featureLevel);

	public ShaderDesc(IntPtr handle) : base(handle, _destroy)
	{
	}

	public static ShaderDesc FromFile(string path, string entry, ShaderType type, ShaderFeatureLevel featureLevel = ShaderFeatureLevel.DX_V4)
	{
		return new ShaderDesc(_createFile(path, entry, type, featureLevel));
	}

	public static ShaderDesc FromSource(string source, string entry, ShaderType type, ShaderFeatureLevel featureLevel = ShaderFeatureLevel.DX_V4)
	{
		return new ShaderDesc(_createSrc(source, entry, type, featureLevel));
	}
}
