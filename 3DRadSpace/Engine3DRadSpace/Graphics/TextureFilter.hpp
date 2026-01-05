#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class TextureFilter : unsigned char
	{
		Anisotropic,
		Linear,
		LinearMipPoint,
		MinLinearMagPointMipLinear,
		MinLinearMagPointMipPoint,
		MinPointMagLinearMipLinear,
		MinPointMagLinearMipPoint,
		Point,
		PointMipLinear
	};
}