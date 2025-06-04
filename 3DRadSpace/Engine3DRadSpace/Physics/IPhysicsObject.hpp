#pragma once
#include "../Objects/IObject3D.hpp"

namespace Engine3DRadSpace::Physics
{
	class DLLEXPORT IPhysicsObject
	{
	protected:
		IPhysicsObject() = default;
	public:
		float Mass = 0;

		float LinearDamping = 0;
		float AngularDamping = 0;

		float StaticFriction = 0;
		float DynamicFriction = 0;
		float Restitution = 0;

		Math::Vector3 LinearVelocity = Math::Vector3::Zero();
		Math::Vector3 AngularVelocity = Math::Vector3::Zero();

		Math::Vector3 MaxAngularVelocity = Math::Vector3::Zero();

		/// <summary>
		/// If true, the fields Position, Rotation, Scale, Mass, Damping, Velocity, etc will be set after a ::Update() call ends.
		/// </summary>
		bool UpdatePropertiesAfterFrame = false;

		enum class PhysicsProperty
		{
			Mass,
			Position,
			Rotation,
			Scale,
			LinearVelocity,
			AngularVelocity,
			MaxAngularVelocity,
			StaticFriction,
			DynamicFriction,
			Restitution,
		};

		/// <summary>
		/// Will apply the chooosen property from the argument. Argument will be read from the class itself. <br/>
		/// For example <c>Apply(PhysicsProperty::Mass)</c> will set the mass to this->Mass.
		/// </summary>
		/// <param name="newSettigs">Selected property</param>
		/// <returns>true if successful.</returns>
		virtual bool Apply(PhysicsProperty newSettigs) = 0;
		virtual bool Read(PhysicsProperty property) const = 0;

		virtual bool ApplyForce(const Math::Vector3& force) = 0;
		virtual bool ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		virtual bool ApplyTorque(const Math::Vector3& force) = 0;

		virtual bool ApplyAcceleration(const Math::Vector3& acc) = 0;
		virtual bool ApplyAngularAcceleration(const Math::Vector3& acc) = 0;

		virtual ~IPhysicsObject() = default;
	};
}