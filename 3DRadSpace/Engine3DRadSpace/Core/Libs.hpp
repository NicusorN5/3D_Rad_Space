#pragma once

#pragma region STL imports
#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>
#include <span>
#include <sal.h>
#include <array>
#include <format>
#include <chrono>
#include <numbers>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <set>
#include <variant>
#include <any>
#include <map>
#include <typeindex>
#include <cassert>
#include <ranges>
#include <random>
#include <fstream>
#include <expected>
#include <concepts>
#pragma endregion

#pragma region WIN32 imports
#ifdef _WIN32
#define NOMINMAX
#include <wrl/client.h>
#pragma endregion

#pragma region Other defines
#if _DEBUG
#define _DISABLE_VECTOR_ANNOTATION
#endif 
#pragma endregion

#pragma region GAPI macros
//Check if compiling for DirectX 11/12 or Vulkan.
#ifndef USING_DX11
#ifndef USING_DX12
#ifndef USING_VULKAN
//#warning "Using DirectX11 as default backend."
#define USING_DX11
#endif
#endif // !USING_DX11
#endif

#ifdef USING_DX11
#ifndef _WIN32
#error DirectX11 is only supported on Windows!
#endif // !_WIN32
#endif

#ifdef _DX12
#ifndef _WIN32
#error DirectX12 is only supported on Windows!
#endif // !_WIN32
#endif

#ifdef USING_DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#endif //USING_DX11
#endif //_WIN32
#pragma endregion

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

#ifndef E3DRSP_INPUT_EXPORT
#if _WIN32
#define E3DRSP_INPUT_EXPORT
#else
#define E3DRSP_INPUT_EXPORT
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

#pragma region Typedefs and usings
using STD_UPtrTypeless = std::unique_ptr<void, std::function<void(void*)>>;
#pragma endregion