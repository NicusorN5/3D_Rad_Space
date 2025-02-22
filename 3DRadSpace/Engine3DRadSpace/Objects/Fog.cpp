#include "Fog.hpp"
#include "../Game.hpp"
#include "../Graphics/Rendering/LinearPixelFogEffect.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics::Rendering;

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
	/*
	Assume:

	Perspective projection matrix is:
	
	Projection = (
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0
	) 
	with:
	 -> b = npd * a;
	 -> a = fpd / (npd - fpd);
	
	then:

	b = npd * a => npd = b / a.

	a = fpd / (npd - fpd) => (npd - fpd) * a = fpd
	a * npd - a * fpd = fpd => a * npd = fpd + a * fpd => a * npd = fpd * (1 + a) => fpd = a * npd / (1 + a).

	conclusion:
	-> npd = b / a.
	-> fpd = a * npd / (1 + a)
	*/

	//Projection[3][3]
	float a = _game->Projection.M33;
	//Projection[3][4]
	float b = _game->Projection.M34;
	//Near plane distance, recovered from projection matrix as above.
	float npd = b / a;
	//Far plane distance, calculated as above from projection matrix.
	float fpd = a * npd / (1 + a);

	_effect->Enabled = Enabled;
	_effect->FogColor = FogColor;

	//Multiply with fpd to convert to normalized space [0,1] used in the depth buffer.
	_effect->FogBegin = FogBegin / fpd;
	_effect->FogEnd = FogEnd / fpd;
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