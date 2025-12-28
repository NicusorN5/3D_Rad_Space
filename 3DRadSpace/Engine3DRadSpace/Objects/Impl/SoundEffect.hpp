#pragma once
#include "../IObject.hpp"
#include "../../Audio/Sound.hpp"
#include "../../Audio/SoundInstance.hpp"
#include "../../Reflection/Reflection.hpp"
#include "../../Core/GetSet.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefSound = Content::AssetID<Audio::Sound>;

	class E3DRSP_OBJECTS_IMPL_EXPORT SoundEffect : public IObject
	{
		Audio::Sound* _sound;
		std::unique_ptr<std::string> _path;
		
		std::unique_ptr<Audio::SoundInstance> _instance;

		float _volume;
		float _getVolume() const noexcept;
		void _setVolume(float f) noexcept;

		float _pitch;
		float _getPitch() const noexcept;
		void _setPitch(float p) noexcept;
		
		bool _looping;
		bool _getLooping() const noexcept;
		void _setLooping(bool looping) noexcept;
	public:
		SoundEffect();

		SoundEffect(
			const std::string& name,
			bool enabled,
			RefSound sound
		);

		SoundEffect(
			const std::string& name,
			bool enabled,
			const std::filesystem::path& path
		);

		RefSound Sound;

		Audio::Sound* GetSound() const noexcept;
		Audio::SoundInstance* GetInstance() const noexcept;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Update() override;

		/// <summary>
		/// Plays the sound.
		/// </summary>
		void Enable() override;
		/// <summary>
		/// Pauses the sound.
		/// </summary>
		void Disable() override;
		/// <summary>
		/// Plays the sound if stopped, and vice-versa.
		/// </summary>
		bool Switch() override;

		Reflection::UUID GetUUID() const noexcept override;

		Gizmos::IGizmo* GetGizmo() const noexcept;

		GetSet<float, SoundEffect, &SoundEffect::_getVolume, &SoundEffect::_setVolume> Volume;
		GetSet<float, SoundEffect, &SoundEffect::_getPitch, &SoundEffect::_setPitch> Pitch;
		GetSet<bool, SoundEffect, &SoundEffect::_getLooping, &SoundEffect::_setLooping> Looping;

		~SoundEffect() = default;
	};

	REFL_FWD(SoundEffect)
}