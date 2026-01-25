using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

[StructLayout(LayoutKind.Sequential)]
public struct RenderTargetBlendState
{
	public byte EnableBlending;
	public Blend SourceBlend;
	public Blend DestinationBlend;
	public BlendOperation BlendOp;
	public Blend SourceBlendAlpha;
	public Blend DestinationBlendAlpha;
	public BlendOperation BlendOpAlpha;
	public ColorWriteEnable WriteMask;
}
