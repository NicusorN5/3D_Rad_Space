using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Math;

[StructLayout(LayoutKind.Sequential, Pack = sizeof(float), Size = 4 * sizeof(float))]
public struct Color
{
	public float R;
	public float G;
	public float B;
	public float A;

	public Color(float r, float g, float b, float a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

	public Color(float r, float g, float b)
	{
		R = r;
		G = g;
		B = b;
		A = 1.0f;
	}
}
