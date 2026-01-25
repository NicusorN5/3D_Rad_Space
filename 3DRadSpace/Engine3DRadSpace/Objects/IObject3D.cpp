#include "IObject3D.hpp"
#include "IObject3D.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

IObject3D::IObject3D(const std::string &name, bool enabled, bool visible, const Vector3&pos, const Vector3&pivot,
					 const Quaternion& rotation, const Vector3& scale) :
	IObject(name, enabled, visible),
	Position(pos),
	RotationCenter(pivot),
	Rotation(rotation),
	Scale(scale)
{
}

Matrix4x4 IObject3D::GetModelMartix()
{
	return 
		Matrix4x4::CreateScale(Scale) *
		Matrix4x4::CreateTranslation(-RotationCenter) *
		Matrix4x4::CreateFromQuaternion(Rotation) *
		Matrix4x4::CreateTranslation(Position);
}

E3DRSP_Vector3 E3DRSP_IObject3D_GetPosition(E3DRSP_IObject3D object)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<IObject3D*>(object)->Position);
}

void E3DRSP_IObject3D_SetPosition(E3DRSP_IObject3D object, const E3DRSP_Vector3* pos)
{
	static_cast<IObject3D*>(object)->Position = std::bit_cast<const Vector3>(*pos);
}

E3DRSP_Vector3 E3DRSP_IObject3D_GetRotationCenter(E3DRSP_IObject3D object)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<IObject3D*>(object)->RotationCenter);
}

void E3DRSP_IObject3D_SetRotationCenter(E3DRSP_IObject3D object, const E3DRSP_Vector3* center)
{
	static_cast<IObject3D*>(object)->RotationCenter = std::bit_cast<const Vector3>(*center);
}

E3DRSP_Quaternion E3DRSP_IObject3D_GetRotation(E3DRSP_IObject3D object)
{
	return std::bit_cast<E3DRSP_Quaternion>(static_cast<IObject3D*>(object)->Rotation);
}

void E3DRSP_IObject3D_SetRotation(E3DRSP_IObject3D object, const E3DRSP_Quaternion* rotation)
{
	static_cast<IObject3D*>(object)->Rotation = std::bit_cast<const Quaternion>(*rotation);
}

E3DRSP_Vector3 E3DRSP_IObject3D_GetScale(E3DRSP_IObject3D object)
{
	return std::bit_cast<E3DRSP_Vector3>(static_cast<IObject3D*>(object)->Scale);
}

void E3DRSP_IObject3D_SetScale(E3DRSP_IObject3D object, const E3DRSP_Vector3* scale)
{
	static_cast<IObject3D*>(object)->Scale = std::bit_cast<const Vector3>(*scale);
}

E3DRSP_Matrix4x4 E3DRSP_IObject3D_GetModelMatrix(E3DRSP_IObject3D object)
{
	return std::bit_cast<E3DRSP_Matrix4x4>(static_cast<IObject3D*>(object)->GetModelMartix());
}

float E3DRSP_IObject3D_Intersects(E3DRSP_IObject3D object, const E3DRSP_Ray* ray)
{
	return static_cast<IObject3D*>(object)->Intersects(std::bit_cast<const Ray>(*ray));
}