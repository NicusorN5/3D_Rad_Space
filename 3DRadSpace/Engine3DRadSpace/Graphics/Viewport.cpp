#include "Viewport.hpp"
#include "Viewport.h"
#include "Math/Math.hpp"
#include "Math/Vector3.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

Vector3 Viewport::Unproject(const Vector3 &source, const Matrix4x4& projection, const Matrix4x4& view, const Matrix4x4& world) const
{
	//https://github.com/MonoGame/MonoGame/blob/develop/MonoGame.Framework/Graphics/Viewport.cs
	auto matrix = Matrix4x4::Invert(world * view * projection);

	Vector3 s = source;
	s.X = (((source.X - ScreenRectangle.X) / ((float)ScreenRectangle.Width) * 2.0f) - 1.0f);
	s.Y = -((((source.Y - ScreenRectangle.Y) / ((float)ScreenRectangle.Height)) * 2.0f) - 1.0f);
	s.Z = (source.Z - this->MinDepth) / (this->MaxDepth - this->MinDepth);

	Vector3 vector = Vector3::Transform(s, matrix);
	float a = (((s.X * matrix.M14) + (s.Y * matrix.M24)) + (s.Z * matrix.M34)) + matrix.M44;
	//float a = (((source.X * matrix.M41) + (source.Y * matrix.M42)) + (source.Z * matrix.M43)) + matrix.M44;
	
	if (!Math::WithinEpsilon(a, 1.0f))
	{
		vector.X = vector.X / a;
		vector.Y = vector.Y / a;
		vector.Z = vector.Z / a;
	}
	return vector;
}

E3DRSP_Vector3 E3DRSP_Viewport_Unproject(
	const E3DRSP_Viewport* viewport,
	const E3DRSP_Vector3* source,
	const E3DRSP_Matrix4x4* projection,
	const E3DRSP_Matrix4x4* view,
	const E3DRSP_Matrix4x4* world
)
{
	Viewport vp = *reinterpret_cast<const Viewport*>(viewport);
	Vector3 src = *reinterpret_cast<const Vector3*>(source);
	Matrix4x4 proj = *reinterpret_cast<const Matrix4x4*>(projection);
	Matrix4x4 v = *reinterpret_cast<const Matrix4x4*>(view);
	Matrix4x4 w = *reinterpret_cast<const Matrix4x4*>(world);
	
	Vector3 result = vp.Unproject(src, proj, v, w);
	return E3DRSP_Vector3{ result.X, result.Y, result.Z };
}