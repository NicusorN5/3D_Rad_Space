#pragma once
#include "Camera.hpp"
#include "../../Input/Key.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT FreeCam : public Camera
	{
		Math::Vector2 _camCoords;
		Math::Vector3 _fwd;
	public:
		FreeCam();

		float Sensitivity = 0.01f;
		float MovementSpeed = 1.0f;
		bool InvertX = false;
		bool InvertY = false;

		Input::Key Forward = Input::Key::W;
		Input::Key Backward = Input::Key::S;
		Input::Key Left = Input::Key::A;
		Input::Key Right = Input::Key::D;
		Input::Key Elevate = Input::Key::Q;
		Input::Key Descend = Input::Key::E;

		Math::Vector3 ForwardDir() const noexcept;
		void SetCameraRotation(const Math::Vector2& camCoords) noexcept;

		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}