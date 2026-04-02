#pragma once
#include "ExitFade.h"
#include "../../../Objects/Impl/ExitFade.hpp"

using namespace Engine3DRadSpace::Objects;

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

void E3DRSP_Camera_SetFadeColor(E3DRSP_ExitFade exitFade, const E3DRSP_Color* color)
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