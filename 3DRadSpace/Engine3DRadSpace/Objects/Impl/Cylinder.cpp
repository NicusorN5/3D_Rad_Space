#include "Cylinder.hpp"
#include "Cylinder.h"
#include "../../Core/IGame.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Cylinder::Cylinder() : IObject3D("Cylinder", false, true, Vector3::Zero())
{
}

void Cylinder::Initialize()
{
}

void Cylinder::Load()
{
	_cylinder = std::make_unique<Primitives::Cylinder>(GetGraphicsDeviceHandle(), 1.0f, 1.0f, Resolution, Colour);
}

void Cylinder::Load(const std::filesystem::path& path)
{
	(void)path;
	Load();
}

void Cylinder::Update()
{
}

void Cylinder::Draw3D()
{
	if(_cylinder && Visible)
	{
		auto game = static_cast<Game*>(_game);
		_cylinder->Transform = this->GetModelMatrix();
		_cylinder->View = game->View;
		_cylinder->Projection = game->Projection;
		_cylinder->Draw3D();
	}
}

float Cylinder::Intersects(const Math::Ray& r)
{
	return r.Intersects(BoundingSphere(Position, Radius));
}

Math::Matrix4x4 Cylinder::GetModelMatrix()
{
	return Matrix4x4::CreateScale({Radius, Height, Radius}) * Matrix4x4::CreateTranslation(Position);
}

Gizmos::IGizmo* Cylinder::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Cylinder>(this);
}

Reflection::UUID Cylinder::GetUUID() const noexcept
{
	// {1260D6C2-FDD3-41A3-949E-AC2FD647253C}
	return {0x1260d6c2, 0xfdd3, 0x41a3, { 0x94, 0x9e, 0xac, 0x2f, 0xd6, 0x47, 0x25, 0x3c }};
}

REFL_BEGIN(Cylinder, "Cylinder", "3D Primitives", "3D box")
	REFL_FIELD(Cylinder, std::string, Name, "Name", "Cylinder", "Object's name")
	REFL_FIELD(Cylinder, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(Cylinder, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
	REFL_FIELD(Cylinder, float, Radius, "Radius", 1.0f, "Scale")
	REFL_FIELD(Cylinder, float, Height, "Height", 1.0f, "Scale")
	REFL_FIELD(Cylinder, Color, Colour, "Color", Colors::White, "Color")
	REFL_FIELD(Cylinder, unsigned, Resolution, "Resolution", 64, "Sphere model tesselation")
REFL_END

E3DRSP_OCylinder E3DRSP_OCylinder_Create()
{
	return new Cylinder();
}

E3DRSP_Color E3DRSP_OCylinder_GetColor(E3DRSP_OCylinder cylinder)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Cylinder*>(cylinder)->Colour);
}

void E3DRSP_OCylinder_SetColor(E3DRSP_OCylinder cylinder, const E3DRSP_Color* color)
{
	static_cast<Cylinder*>(cylinder)->Colour = std::bit_cast<Color>(*color);
}

float E3DRSP_OCylinder_GetRadius(E3DRSP_OCylinder cylinder)
{
	return static_cast<Cylinder*>(cylinder)->Radius;
}

void E3DRSP_OCylinder_SetRadius(E3DRSP_OCylinder cylinder, float radius)
{
	static_cast<Cylinder*>(cylinder)->Radius = radius;
}

float E3DRSP_OCylinder_GetHeight(E3DRSP_OCylinder cylinder)
{
	return static_cast<Cylinder*>(cylinder)->Height;
}

void E3DRSP_OCylinder_SetHeight(E3DRSP_OCylinder cylinder, float height)
{
	static_cast<Cylinder*>(cylinder)->Height = height;
}

unsigned E3DRSP_OCylinder_GetResolution(E3DRSP_OCylinder cylinder)
{
	return static_cast<Cylinder*>(cylinder)->Resolution;
}

void E3DRSP_OCylinder_SetResolution(E3DRSP_OCylinder cylinder, unsigned resolution)
{
	static_cast<Cylinder*>(cylinder)->Resolution = resolution;
}