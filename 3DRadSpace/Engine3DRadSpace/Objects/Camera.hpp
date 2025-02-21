#pragma once
#include "../IObject3D.hpp"
#include "../Math/Math.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 3D Camera.
	/// </summary>
	/// <remarks>
	/// This object updates the view, and projection matrices in the Draw3D() method. You may manually set these matrices without this.
	/// </remarks>
	class DLLEXPORT Camera : public IObject3D
	{
	public:
		Camera(const std::string& name = "Camera", bool visible = true,
		       Math::Vector3 pos = Math::Vector3::Zero(),
		       Math::Vector3 look_at = Math::Vector3::UnitZ(),
		       Math::Vector3 up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f, float fov = Math::ToRadians(65.0f), float npd = 0.01f, float fpd = 500.0f);

		Math::Vector3 UpwardsDir;

		float AspectRatio;
		float FieldOfView;
		float NearPlaneDistance;
		float FarPlaneDistance;

		enum class CameraMode
		{
			UseRotation,
			UseLookAtCoordinates,
		} LookMode;

		Math::Vector3 LookAt;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path &path) override;
	
		void EditorInitialize() override;
		void EditorLoad() override;
		void EditorUpdate() override;

		/// <summary>
		/// Sets the view and projection matrices.
		/// </summary>
		void Draw3D() override;

		/// <summary>
		/// Not used.
		/// </summary>
		void Update() override;

		Math::Matrix4x4 GetModelMartix() override;
		void EditorDraw3D(bool selected) override;

		std::optional<float> Intersects(const Math::Ray &r) override;

		Reflection::UUID GetUUID() const noexcept override;

		~Camera();
	};
}

REFL_FWD(Camera)