#include "Viewport.h"
#include "../../Graphics/Viewport.hpp"

E3DRSP_Vector3 E3DRSP_Viewport_Unproject(
	const E3DRSP_Viewport* viewport,
	const E3DRSP_Vector3* source,
	const E3DRSP_Matrix4x4* projection,
	const E3DRSP_Matrix4x4* view,
	const E3DRSP_Matrix4x4* world
)
{
	Viewport vp = std::bit_cast<const Viewport>(*viewport);
	Vector3 src = std::bit_cast<const Vector3>(*source);
	Matrix4x4 proj = std::bit_cast<const Matrix4x4>(*projection);
	Matrix4x4 v = std::bit_cast<const Matrix4x4>(*view);
	Matrix4x4 w = std::bit_cast<const Matrix4x4>(*world);

	Vector3 result = vp.Unproject(src, proj, v, w);
	return E3DRSP_Vector3{result.X, result.Y, result.Z};
}