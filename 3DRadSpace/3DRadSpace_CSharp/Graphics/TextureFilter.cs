namespace Engine3DRadSpace.Graphics;

public enum TextureFilter : byte
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
