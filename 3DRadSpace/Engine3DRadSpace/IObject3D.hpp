/// ------------------------------------------------------------------------------------------------
/// File:   IObject3D.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "IObject.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "IDrawable3D.hpp"
#include "Math/Ray.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT IObject3D : public IObject, public IDrawable3D
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
		virtual void EditorDraw3D(bool selected) = 0;
		virtual std::optional<float> Intersects(const Math::Ray &r) = 0;

		~IObject3D() = default;
	};
}
