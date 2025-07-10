#pragma once
#include "SoundEffect.hpp"
#include "IObject3D.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_EXPORT SoundSource : public IObject3D
	{
		SoundEffect _underlying;
	public:
		SoundSource() = default;

		void Draw3D() override;
		std::optional<float> Intersects(const Math::Ray & r) override;

		Reflection::UUID GetUUID() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path & path) override;
		void Update() override;
		Objects::Gizmos::IGizmo *GetGizmo() const noexcept override;

		void Enable() override;
		void Disable() override;
		bool Switch() override;

		~SoundSource() = default;
	};
}

REFL_FWD(SoundSource)