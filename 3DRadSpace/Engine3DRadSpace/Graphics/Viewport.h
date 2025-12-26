#pragma once
#include "../Math/Rectangle.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Vector3.h"

typedef struct E3DRSP_Viewport
{
	E3DRSP_RectangleF ScreenRectangle;

	float MinDepth;
	float MaxDepth;
} E3DRSP_Viewport;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_Vector3 E3DRSP_Viewport_Unproject(
		const E3DRSP_Viewport* viewport,
		const E3DRSP_Vector3* source,
		const E3DRSP_Matrix4x4* projection,
		const E3DRSP_Matrix4x4* view,
		const E3DRSP_Matrix4x4* world
	);
#ifdef __cplusplus
}
#endif