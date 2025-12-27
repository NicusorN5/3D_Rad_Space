#pragma once
#include "../Math/Math.hpp"
#include "../Reflection/Reflection.hpp"
#include "../Core/GetSet.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Base type for all objects that update the view/projection matrices.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT ICamera
	{
	public:
		virtual Math::Matrix4x4 GetViewMatrix() const noexcept = 0;
		virtual Math::Matrix4x4 GetProjectionMatrix() const = 0;

		virtual ~ICamera() = default;
	};
}