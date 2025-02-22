#include "Fog.hpp"
#include "../Game.hpp"
#include "../Graphics/Rendering/LinearPixelFogEffect.hpp"
#include "../Math/Vector3.hpp"
#include "../Objects/Camera.hpp"
#include "../ObjectList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics::Rendering;
using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::Objects::Fog::Fog() : 
	Fog("Fog", true, 0.5f, 0.9f, Colors::White)
{
}

Fog::Fog(const std::string& name, bool enabled, float begin, float end, Color color) :
	IObject(name, enabled),
	FogBegin(begin),
	FogEnd(end),
	FogColor(color)
{
}

void Fog::Load()
{
}

void Fog::Initialize()
{
	_effect = &_game->PostProcesses->Add<LinearPixelFogEffect>(_game->Device.get());
	Update();
}

void Fog::Load(const std::filesystem::path& path)
{
}

void Fog::EditorInitialize()
{
	Initialize();
}

void Fog::EditorUpdate()
{
	Update();
}

void Fog::EditorLoad()
{
}

void Fog::Update()
{
	_effect->Enabled = Enabled;
	_effect->FogColor = FogColor;

	_effect->NearPlaneDistance = _game->Objects->GetRenderingCamera()->NearPlaneDistance;
	_effect->FarPlaneDistance = _game->Objects->GetRenderingCamera()->FarPlaneDistance;

	_effect->FogBegin = FogBegin / 500;
	_effect->FogEnd = FogEnd / 500;
}

Reflection::UUID Fog::GetUUID() const noexcept
{
	// {57299A03-31EA-43D2-A58E-C1F865E1EF85}
	return { 0x57299a03, 0x31ea, 0x43d2, { 0xa5, 0x8e, 0xc1, 0xf8, 0x65, 0xe1, 0xef, 0x85 } };
}

REFL_BEGIN(Fog, "Fog", "Post effects", "Post process linear fog")
	REFL_FIELD(Fog, std::string, Name, "Name", "Fog", "Object name")
	REFL_FIELD(Fog, bool, Enabled, "Enabled", true, "Is fog enabled?")
	REFL_FIELD(Fog, float, FogBegin, "Fog Begin (m)", 100.0f, "Fog start distance (meters)")
	REFL_FIELD(Fog, float, FogEnd, "Fog End (m)", 200.0f, "Fog end distance(meters)")
	REFL_FIELD(Fog, Color, FogColor, "Fog Color", Colors::White, "Fog color")
REFL_END