#pragma once
#include "Gizmo.hpp"
#include "../SoundSource.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<SoundSource> final : public IGizmo
	{
		STD_UPtrTypeless _billboard;
		STD_UPtrTypeless _soundImage;
	public:
		Gizmo();

		void Draw3D() override;
		void Draw2D() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		~Gizmo() = default;
	};
}