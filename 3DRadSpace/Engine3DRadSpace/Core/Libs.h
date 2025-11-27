#pragma once

#include <stdint.h>

#ifndef __cplusplus
#include <stdbool.h>
#else
typedef bool _Bool;
#endif

#pragma region Library exports/imports macros
#ifndef E3DRSP_AUDIO_EXPORT
#if _WIN32
#define E3DRSP_AUDIO_EXPORT
#else
#define E3DRSP_AUDIO_EXPORT
#endif
#endif

#ifndef E3DRSP_CONTENT_EXPORT
#if _WIN32
#define E3DRSP_CONTENT_EXPORT
#else
#define E3DRSP_CONTENT_EXPORT
#endif
#endif

#ifndef E3DRSP_CONTENT_ASSETS_EXPORT
#if _WIN32
#define E3DRSP_CONTENT_ASSETS_EXPORT
#else
#define E3DRSP_CONTENT_ASSETS_EXPORT
#endif
#endif

#ifndef E3DRSP_CORE_EXPORT
#if _WIN32
#define E3DRSP_CORE_EXPORT
#else
#define E3DRSP_CORE_EXPORT
#endif
#endif

#ifndef E3DRSP_GAMES_EXPORT
#if _WIN32
#define E3DRSP_GAMES_EXPORT
#else
#define E3DRSP_GAMES_EXPORT
#endif
#endif

#ifndef E3DRSP_GRAPHICS_EXPORT
#if _WIN32
#define E3DRSP_GRAPHICS_EXPORT
#else
#define E3DRSP_GRAPHICS_EXPORT
#endif
#endif

#ifndef E3DRSP_GRAPHICS_DX11_EXPORT
#if _WIN32
#define E3DRSP_GRAPHICS_DX11_EXPORT
#else
#define E3DRSP_GRAPHICS_DX11_EXPORT
#endif
#endif

#ifndef E3DRSP_GRAPHICS_NULL_EXPORT
#if _WIN32
#define E3DRSP_GRAPHICS_NULL_EXPORT
#else
#define E3DRSP_GRAPHICS_NULL_EXPORT
#endif
#endif


#ifndef E3DRSP_GRAPHICS_PRIMITIVES_EXPORT
#if _WIN32
#define E3DRSP_GRAPHICS_PRIMITIVES_EXPORT
#else
#define E3DRSP_GRAPHICS_PRIMITIVES_EXPORT
#endif
#endif

#ifndef E3DRSP_GRAPHICS_RENDERING_EXPORT
#if _WIN32
#define E3DRSP_GRAPHICS_RENDERING_EXPORT
#else
#define E3DRSP_GRAPHICS_RENDERING_EXPORT
#endif
#endif

#ifndef E3DRSP_GRAPHICS_SHADERS_EXPORT
#if _WIN32
#define E3DRSP_GRAPHICS_SHADERS_EXPORT
#else
#define E3DRSP_GRAPHICS_SHADERS_EXPORT
#endif
#endif


#ifndef E3DRSP_INPUT_EXPORT
#if _WIN32
#define E3DRSP_INPUT_EXPORT
#else
#define E3DRSP_INPUT_EXPORT
#endif
#endif

#ifndef E3DRSP_LOGGING_EXPORT
#if _WIN32
#define E3DRSP_LOGGING_EXPORT
#else
#define E3DRSP_LOGGING_EXPORT
#endif
#endif

#ifndef E3DRSP_MATH_EXPORT
#if _WIN32
#define E3DRSP_MATH_EXPORT
#else
#define E3DRSP_MATH_EXPORT
#endif
#endif

#ifndef E3DRSP_NATIVE_EXPORT
#if _WIN32
#define E3DRSP_NATIVE_EXPORT
#else
#define E3DRSP_NATIVE_EXPORT
#endif
#endif

#ifndef E3DRSP_OBJECTS_EXPORT
#if _WIN32
#define E3DRSP_OBJECTS_EXPORT
#else
#define E3DRSP_OBJECTS_EXPORT
#endif
#endif

#ifndef E3DRSP_PHYSICS_EXPORT
#if _WIN32
#define E3DRSP_PHYSICS_EXPORT
#else
#define E3DRSP_PHYSICS_EXPORT
#endif
#endif

#ifndef E3DRSP_PLUGINS_EXPORT
#if _WIN32
#define E3DRSP_PLUGINS_EXPORT
#else
#define E3DRSP_PLUGINS_EXPORT
#endif
#endif

#ifndef E3DRSP_PROJECTS_EXPORT
#if _WIN32
#define E3DRSP_PROJECTS_EXPORT
#else
#define E3DRSP_PROJECTS_EXPORT
#endif
#endif

#ifndef E3DRSP_REFLECTION_EXPORT
#if _WIN32
#define E3DRSP_REFLECTION_EXPORT
#else
#define E3DRSP_REFLECTION_EXPORT
#endif
#endif

#ifndef E3DRSP_SCRIPTING_EXPORT
#if _WIN32
#define E3DRSP_SCRIPTING_EXPORT
#else
#define E3DRSP_SCRIPTING_EXPORT
#endif
#endif
#pragma endregion