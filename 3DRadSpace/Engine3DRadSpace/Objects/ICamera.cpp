#include "ICamera.hpp"
#include "ICamera.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

ICamera::ICamera(
	const Math::Vector3& normal,
	const Math::Vector3& lookAt,
	float aspectRatio,
	float fov,
	float npd,
	float fpd
) :
	Normal(normal),
	LookAt(lookAt),
	AspectRatio(aspectRatio),
	FieldOfView(fov),
	NearPlaneDistance(npd),
	FarPlaneDistance(fpd)
{
}

E3DRSP_Matrix4x4 E3DRSP_ICamera_GetViewMatrix(E3DRSP_ICamera cam)
{
	return std::bit_cast<E3DRSP_Matrix4x4>(static_cast<ICamera*>(cam)->GetViewMatrix());
}

E3DRSP_Matrix4x4 E3DRSP_ICamera_GetProjectionMatrix(E3DRSP_ICamera cam)
{
	return std::bit_cast<E3DRSP_Matrix4x4>(static_cast<ICamera*>(cam)->GetProjectionMatrix());
}
void E3DRSP_ICamera_Destroy(E3DRSP_ICamera cam)
{
	delete static_cast<ICamera*>(cam);
}