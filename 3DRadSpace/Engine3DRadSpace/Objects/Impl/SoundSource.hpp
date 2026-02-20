#pragma once
#include "SoundEffect.hpp"
#include "../IObject3D.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT SoundSource : public IObject3D
	{
		SoundEffect _underlying;

		RefSound _getAsset() const noexcept;
		void _setAsset(RefSound sound) noexcept;

		float _volume;
		float _getVolume() const noexcept;
		void _setVolume(float volume) noexcept;

		float _pitch;
		float _getPitch() const noexcept;
		void _setPitch(float pitch) noexcept;

		bool _looping;
		bool _getLooping() const noexcept;
		void _setLooping(bool looping) noexcept;

		Math::Vector3 _velocity;
		Math::Vector3 _getVelocity() const noexcept;
		void _setVelocity(const Math::Vector3& velocity) noexcept;

		Math::Vector3 _direction;
		Math::Vector3 _getDirection() const noexcept;
		void _setDirection(const Math::Vector3& velocity) noexcept;

		float _maxDistance;
		float _getMaxDistance() const noexcept;
		void _setMaxDistance(float dst) noexcept;

		float _referenceDistance;
		float _getReferenceDistance() const noexcept;
		void _setReferenceDistance(float refDst) noexcept;

		float _rolloffFactor;
		float _getRolloffFactor() const noexcept;
		void _setRolloffFactor(float rollOff) noexcept;

		float _coneInnerAngle;
		float _getConeInnerAngle() const noexcept;
		void _setConeInnerAngle(float innerAngle) noexcept;

		float _coneOuterAngle;
		float _getConeOuterAngle() const noexcept;
		void _setConeOuterAngle(float outerAngle) noexcept;

		float _coneOuterGain;
		float _getConeOuterGain() const noexcept;
		void _setConeOuterGain(float outerGain) noexcept;
	public:
		SoundSource();

		SoundSource(
			const std::string &name,
			bool enabled,
			RefSound sound,
			const Math::Vector3 &position
		);

		SoundSource(
			const std::string &name,
			bool enabled,
			const std::filesystem::path& soundFile,
			const Math::Vector3 &position
		);

		void Draw3D() override;
		float Intersects(const Math::Ray &r) override;

		Reflection::UUID GetUUID() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path & path) override;
		void Update() override;
		Objects::Gizmos::IGizmo *GetGizmo() const noexcept override;

		void Enable() override;
		void Disable() override;
		bool Switch() override;

		GetSet<RefSound, SoundSource, &SoundSource::_getAsset, &SoundSource::_setAsset> Sound;

		GetSet<float, SoundSource, &SoundSource::_getVolume, &SoundSource::_setVolume> Volume;
		GetSet<float, SoundSource, &SoundSource::_getPitch, &SoundSource::_setPitch> Pitch;
		GetSet<bool, SoundSource, &SoundSource::_getLooping, &SoundSource::_setLooping> Looping;

		GetSet<Math::Vector3, SoundSource, &_getVelocity, &_setVelocity> Velocity;
		GetSet<Math::Vector3, SoundSource, &_getDirection, &_setDirection> Direction;

		GetSet<float, SoundSource, &_getMaxDistance, &_setMaxDistance> MaxDistance;
		GetSet<float, SoundSource, &_getReferenceDistance, &_setReferenceDistance> ReferenceDistance;
		GetSet<float, SoundSource, &_getRolloffFactor, &_setRolloffFactor> RolloffFactor;
		GetSet<float, SoundSource, &_getConeInnerAngle, &_setConeInnerAngle> ConeInnerAngle;
		GetSet<float, SoundSource, &_getConeOuterAngle, &_setConeOuterAngle> ConeOuterAngle;
		GetSet<float, SoundSource, &_getConeOuterGain, &_setConeOuterGain> ConeOuterGain;
		
		Audio::Sound* GetSound() const noexcept;
		Audio::SoundInstance* GetInstance() const noexcept;

		~SoundSource() = default;
	};
}

REFL_FWD(SoundSource)