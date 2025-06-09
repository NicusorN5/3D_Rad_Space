#pragma once
#include "Gizmo.hpp"
#include "../Skinmesh.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_EXPORT Gizmo<Skinmesh> final: public IGizmo
	{
		bool _wasLoaded = false;
		STD_UPtrTypeless _wireframe_RasterizerState;
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