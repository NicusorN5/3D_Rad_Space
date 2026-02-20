#include "ExitFade.hpp"
#include "ExitFade.h"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

ExitFade::ExitFade(const std::string& name, const std::filesystem::path& projectPath, Color fadeColor, float fadeTime) :
	IObject2D(name, false),
	ProjectPath(projectPath.string()),
	FadeColor(fadeColor),
	FadeTime(fadeTime)
{
}

void ExitFade::Update()
{
	if(!Enabled) return;
}

void ExitFade::Draw2D()
{
	if(!Enabled) return;
	auto game = static_cast<Game*>(_game);

	_timer += game->Draw_dt;

	if(_timer >= FadeTime)
	{
		if(ProjectPath.empty())
			_game->Exit();
		else
		{
			game->AppendScene(ProjectPath);
		}
	}
}

void ExitFade::Initialize()
{
}

void ExitFade::Load()
{
}

void ExitFade::Load(const std::filesystem::path& path)
{
	ProjectPath = path.string();
}

Reflection::UUID ExitFade::GetUUID() const noexcept
{
	// {1243BB88-6FF5-43AD-97D6-8907FAE54528}
	return { 0x1243bb88, 0x6ff5, 0x43ad, { 0x97, 0xd6, 0x89, 0x7, 0xfa, 0xe5, 0x45, 0x28 } };
}

Gizmos::IGizmo* ExitFade::GetGizmo() const noexcept
{
	return nullptr;
}

REFL_BEGIN(ExitFade, "ExitFade", "Events", "Loads an other scene, or exits the game")
	REFL_FIELD(ExitFade, std::string, Name, "Name", "ExitFade", "Object name")
	REFL_FIELD(ExitFade, std::string, ProjectPath, "Path to new project", "", "Project to load, empty if closing the game")
	REFL_FIELD(ExitFade, Color, FadeColor, "Fade color", Colors::Black, "Fade out color")
	REFL_FIELD(ExitFade, float, FadeTime, "Fade time", 5.0f, "Fade out time")
REFL_END

E3DRSP_ExitFade E3DRSP_ExitFade_Create()
{
	return new ExitFade();
}

const char* E3DRSP_Camera_GetProjectPath(E3DRSP_ExitFade exitFade)
{
	return static_cast<ExitFade*>(exitFade)->ProjectPath.c_str();
}

void E3DRSP_Camera_SetProjectPath(E3DRSP_ExitFade exitFade, const char* path)
{
	static_cast<ExitFade*>(exitFade)->ProjectPath = path;
}

E3DRSP_Color E3DRSP_Camera_GetFadeColor(E3DRSP_ExitFade exitFade)
{
	return std::bit_cast<E3DRSP_Color>(static_cast<ExitFade*>(exitFade)->FadeColor);
}

void E3DRSP_Camera_SetFadeColor(E3DRSP_ExitFade exitFade, const E3DRSP_Color *color)
{
	static_cast<ExitFade*>(exitFade)->FadeColor = {color->R, color->G, color->B, color->A};
}

float E3DRSP_Camera_GetFadeTime(E3DRSP_ExitFade exitFade)
{
	return static_cast<ExitFade*>(exitFade)->FadeTime;
}

void E3DRSP_Camera_SetFadeTime(E3DRSP_ExitFade exitFade, float timeMs)
{
	static_cast<ExitFade*>(exitFade)->FadeTime = timeMs;
}