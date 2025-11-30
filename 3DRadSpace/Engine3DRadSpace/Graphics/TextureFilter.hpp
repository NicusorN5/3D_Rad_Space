#pragma once

namespace Engine3DRadSpace::Graphics
{
	enum class TextureFilter
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