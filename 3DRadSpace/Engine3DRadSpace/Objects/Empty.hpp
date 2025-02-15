/// ------------------------------------------------------------------------------------------------
/// File:   Objects/Empty.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#pragma once
#include "..\IObject3D.hpp"
#include "..\Reflection\Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a blank object, with no behiavour. Can be used as a dummy, or plain 3D transform.
	/// </summary>
	class DLLEXPORT Empty : public IObject3D
	{
	public:
		Empty(const std::string& name = "", const Math::Vector3& pos = {0,0,0}, const Math::Vector3& pivot = {0,0,0},
			  const Math::Quaternion& rot = Math::Quaternion(), const Math::Vector3& scale = {1,1,1});

		// Inherited via IObject3D
		void Initialize() override;

		void Update() override;

		void Load() override;

		void Load(const std::filesystem::path& path) override;

		void EditorInitialize() override;

		void EditorLoad() override;

		Reflection::UUID GetUUID() const noexcept override;

		void Draw3D() override;

		void EditorDraw3D(bool selected) override;

		std::optional<float> Intersects(const Math::Ray& r) override;
	};
}

REFL_FWD(Empty)