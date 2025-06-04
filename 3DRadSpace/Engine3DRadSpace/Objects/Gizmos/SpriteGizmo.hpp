#pragma once
#include "Gizmo.hpp"
#include "../Sprite.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class DLLEXPORT Gizmo<Sprite> : public IGizmo
	{
	public:
		Gizmo();

		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Draw3D() override;
		void Draw2D() override;

		void Update() override;

		~Gizmo() = default;
	};
}