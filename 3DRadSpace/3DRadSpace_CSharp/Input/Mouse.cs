using System.Runtime.InteropServices;
using Engine3DRadSpace.Internal;

namespace Engine3DRadSpace.Input;

[StructLayout(LayoutKind.Sequential)]
public struct Mouse
{
	public ButtonState Left { get; internal set; }
	public ButtonState MiddleButton { get; internal set; }
	public ButtonState RightButton { get; internal set; }
	public Point Position { get; internal set; }
	public float ScrollWheel { get; internal set; }
}
