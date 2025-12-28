#include "IObject2D.hpp"
#include "IObject2D.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

IObject2D::IObject2D(const std::string &name, bool enabled, bool visible, const Vector2&pos, const
                     Vector2&scale, 
                     float rotation, const Vector2&pivot, float depth) :
	IObject(name, false, false),
	Position(pos),
	Rotation(rotation),
	RotationCenter(pivot),
	Scale(scale),
	Depth(depth)
{
}

E3DRSP_Vector2 E3DRSP_IObject2D_GetPosition(E3DRSP_IObject2D object)
{
	return std::bit_cast<E3DRSP_Vector2>(static_cast<IObject2D*>(object)->Position);
}

void E3DRSP_IObject2D_SetPosition(E3DRSP_IObject2D object, const E3DRSP_Vector2* pos)
{
	static_cast<IObject2D*>(object)->Position = std::bit_cast<Vector2>(*pos);
}

E3DRSP_Vector2 E3DRSP_IObject2D_GetRotationCenter(E3DRSP_IObject2D object)
{
	return std::bit_cast<E3DRSP_Vector2>(static_cast<IObject2D*>(object)->RotationCenter);
}

void E3DRSP_IObject2D_SetRotationCenter(E3DRSP_IObject2D object, const E3DRSP_Vector2* center)
{
	static_cast<IObject2D*>(object)->RotationCenter = std::bit_cast<Vector2>(*center);
}

float E3DRSP_IObject2D_GetRotation(E3DRSP_IObject2D object)
{
	return static_cast<IObject2D*>(object)->Rotation;
}
void E3DRSP_IObject2D_SetRotation(E3DRSP_IObject2D object, float rotation)
{
	static_cast<IObject2D*>(object)->Rotation = rotation;
}

E3DRSP_Vector2 E3DRSP_IObject2D_GetScale(E3DRSP_IObject2D object)
{
	return std::bit_cast<E3DRSP_Vector2>(static_cast<IObject2D*>(object)->Scale);
}

void E3DRSP_IObject2D_SetScale(E3DRSP_IObject2D object, const E3DRSP_Vector2* scale)
{
	static_cast<IObject2D*>(object)->Scale = std::bit_cast<Vector2>(*scale);
}

float E3DRSP_IObject2D_GetDepth(E3DRSP_IObject2D object)
{
	return static_cast<IObject2D*>(object)->Depth;
}

void E3DRSP_IObject2D_SetDepth(E3DRSP_IObject2D object, float depth)
{
	static_cast<IObject2D*>(object)->Depth = depth;
}