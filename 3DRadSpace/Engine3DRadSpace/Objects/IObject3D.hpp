#pragma once
#include "IObject.hpp"
#include "IDrawable3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace
{
	class E3DRSP_OBJECTS_EXPORT IObject3D : public IObject, public IDrawable3D
	{
	protected:
		explicit IObject3D(const std::string& name = "", bool enabled = false, bool visible = false, const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Vector3& pivot = Math::Vector3::Zero(), const Math::Quaternion& rotation = Math::Quaternion(), const Math::Vector3& scale = Math::Vector3::One());
	public:
		Math::Vector3 Position;

		Math::Vector3 RotationCenter;
		Math::Quaternion Rotation;

		Math::Vector3 Scale;

		virtual Math::Matrix4x4 GetModelMartix();
		virtual std::optional<float> Intersects(const Math::Ray &r) = 0;

		~IObject3D() = default;
	};
}
