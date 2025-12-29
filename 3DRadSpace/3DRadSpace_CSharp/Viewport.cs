using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	[StructLayout(LayoutKind.Sequential)]
	public struct Viewport
	{
		public Viewport(Internal.RectangleF r, float mind, float maxd)
		{
			ScreenRectangle = r;
			MinDepth = mind;
			MaxDepth = maxd;
		}

		public Internal.RectangleF ScreenRectangle;

		public float MinDepth;
		public float MaxDepth;
	}
}
