#pragma once
#include "IObject3D.hpp"
#include "../Math/Math.hpp"
#include "../Reflection/Reflection.hpp"
#include "../Core/GetSet.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 3D Camera.
	/// </summary>
	/// <remarks>
	/// This object updates the view, and projection matrices in the Draw3D() method. You may manually set these matrices without this.
	/// </remarks>
	class E3DRSP_OBJECTS_EXPORT Camera : public IObject3D
	{
	public:
		Camera(
			const std::string& name = "Camera",
			bool visible = true,
			const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Vector3 &look_at = Math::Vector3::UnitZ(),
			const Math::Vector3 &up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f, 
			float fov = Math::ToRadians(65.0f), 
			float npd = 0.01f,
			float fpd = 500.0f
		);

		Math::Vector3 Normal;

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


		Math::Matrix4x4 GetModelMartix() override;
		/// <summary>
		/// Gets the View matrix of the camera.
		/// </summary>
		/// <returns>View matrix</returns>
		Math::Matrix4x4 GetViewMatrix() const noexcept;
		Math::Matrix4x4 GetProjectionMatrix() const;

		/// <summary>
		/// Sets the view and projection matrices.
		/// </summary>
		void Draw3D() override;

		/// <summary>
		/// Sets an internal reference in Game::Objects list.
		/// </summary>
		void Update() override;

		/// <summary>
		/// Same as both Draw3D() and Update() as if the camera is enabled.
		/// </summary>
		void ForceUpdate();

		std::optional<float> Intersects(const Math::Ray &r) override;
		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Camera();
	};
}

REFL_FWD(Camera)