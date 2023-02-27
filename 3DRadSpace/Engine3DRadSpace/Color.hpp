#pragma once

namespace Engine3DRadSpace
{
	struct Color
	{
		float R;
		float G;
		float B;
		float A;

		Color(float r = 0.00f, float g = 0.00f, float b = 0.00f, float a = 1.00f) : R(r), G(g), B(b), A(a) {};

		static Color FromRGB(int r, int g, int b, int a = 255);
	};
	namespace Colors
	{
		extern Color White;
		extern Color Red;
		extern Color Green;
		extern Color Blue;
		extern Color Black;
		extern Color Gray;
	};
}
