#include "SoundSource.hpp"
#include "Gizmos.hpp"
#include "Gizmos/SoundSourceGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

void SoundSource::Draw3D()
{
}

std::optional<float> SoundSource::Intersects(const Math::Ray & r)
{
	return r.Intersects(Math::BoundingSphere(Position, 1.0f));
}

Reflection::UUID Engine3DRadSpace::Objects::SoundSource::GetUUID() const noexcept
{
	// {4F91C443-67C3-40C3-9676-A13A84715D2B}
	return {0x4f91c443, 0x67c3, 0x40c3, { 0x96, 0x76, 0xa1, 0x3a, 0x84, 0x71, 0x5d, 0x2b }};
}

void SoundSource::Initialize()
{
	_underlying.Initialize();
}

void SoundSource::Update()
{
	_underlying.Update();
}

void SoundSource::Load()
{
	_underlying.Load();
}

void SoundSource::Load(const std::filesystem::path &path)
{
	_underlying.Load(path);
}

Objects::Gizmos::IGizmo *SoundSource::GetGizmo() const noexcept
{
	return Internal::GizmoOf<SoundSource>(this);
}

void Engine3DRadSpace::Objects::SoundSource::Enable()
{
	_underlying.Enable();
}

void Engine3DRadSpace::Objects::SoundSource::Disable()
{
	_underlying.Disable();
}

bool Engine3DRadSpace::Objects::SoundSource::Switch()
{
	return _underlying.Switch();
}

REFL_BEGIN(SoundSource, "SoundSource", "Sound", "3D Localized sound source")
REFL_FIELD(SoundSource, std::string, Name, "Name", "SoundSource", "Name of the object")
REFL_FIELD(SoundSource, bool, Enabled, "Playing at start",true, "Playing at startup")
REFL_END