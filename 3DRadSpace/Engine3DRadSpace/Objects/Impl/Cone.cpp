#include "Cone.hpp"
#include "Cone.h"
#include "../../Core/IGame.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Cone::Cone() : IObject3D("Cone", false, true, Vector3::Zero()),
	Radius(1.0f),
	Height(1.0f),
	Resolution(64u)
{
}

void Cone::Initialize()
{
}

void Cone::Load()
{
	_cone = std::make_unique<Primitives::Cone>(GetGraphicsDeviceHandle(), 1.0f, 1.0f, Resolution, Colour);
}

void Cone::Load(const std::filesystem::path& path)
{
	(void)path;
	Load();
}

void Cone::Update()
{
}

void Cone::Draw3D()
{
	if(_cone && Visible)
	{
		auto game = static_cast<Game*>(_game);
		_cone->Transform = this->GetModelMatrix();
		_cone->View = game->View;
		_cone->Projection = game->Projection;
		_cone->Draw3D();
	}
}

float Cone::Intersects(const Math::Ray& r)
{
	return r.Intersects(BoundingSphere(Position, Radius));
}

Math::Matrix4x4 Cone::GetModelMatrix()
{
	return Matrix4x4::CreateScale({Radius, Height, Radius}) * Matrix4x4::CreateTranslation(Position);
}

Gizmos::IGizmo* Cone::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Cone>(this);
}

Reflection::UUID Cone::GetUUID() const noexcept
{
	// {1260D6C2-FDD3-41A3-949E-AC2FD647253C}
	return {0x1260d6c2, 0xfdd3, 0x41a3, { 0x94, 0x9e, 0xac, 0x2f, 0xd6, 0x47, 0x25, 0x3c }};
}

REFL_BEGIN(Cone, "Cone", "3D Primitives", "3D box")
	REFL_FIELD(Cone, std::string, Name, "Name", "Cone", "Object's name")
	REFL_FIELD(Cone, bool, Visible, "Visible", true, "Is the object visible?")
	REFL_FIELD(Cone, Vector3, Position, "Position", Vector3::Zero(), "Object's position in world space")
	REFL_FIELD(Cone, float, Radius, "Radius", 1.0f, "Scale")
	REFL_FIELD(Cone, float, Height, "Height", 1.0f, "Scale")
	REFL_FIELD(Cone, Color, Colour, "Color", Colors::White, "Color")
	REFL_FIELD(Cone, unsigned, Resolution, "Resolution", 64, "Sphere model tesselation")
REFL_END

E3DRSP_OCone E3DRSP_OCone_Create()
{
	return new Cone();
}

E3DRSP_Color E3DRSP_OCone_GetColor(E3DRSP_OCone cone)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<Cone*>(cone)->Colour);
}

void E3DRSP_OCone_SetColor(E3DRSP_OCone cone, const E3DRSP_Color* color)
{
	static_cast<Cone*>(cone)->Colour = std::bit_cast<Color>(*color);
}

float E3DRSP_OCone_GetRadius(E3DRSP_OCone cone)
{
	return static_cast<Cone*>(cone)->Radius;
}

void E3DRSP_OCone_SetRadius(E3DRSP_OCone cone, float radius)
{
	static_cast<Cone*>(cone)->Radius = radius;
}

float E3DRSP_OCone_GetHeight(E3DRSP_OCone cone)
{
	return static_cast<Cone*>(cone)->Height;
}

void E3DRSP_OCone_SetHeight(E3DRSP_OCone cone, float height)
{
	static_cast<Cone*>(cone)->Height = height;
}

unsigned E3DRSP_OCone_GetResolution(E3DRSP_OCone cone)
{
	return static_cast<Cone*>(cone)->Resolution;
}

void E3DRSP_OCone_SetResolution(E3DRSP_OCone cone, unsigned resolution)
{
	static_cast<Cone*>(cone)->Resolution = resolution;
}