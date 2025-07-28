#pragma once
#include "Gizmo.hpp"
#include "../Camera.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_EXPORT Gizmo<Camera> final : public IGizmo
	{
		STD_UPtrTypeless _cameraModel;
		STD_UPtrTypeless _cameraPreview;
		STD_UPtrTypeless _cameraPreviewDepth;
		STD_UPtrTypeless _font;

		bool _wasLoaded = false;
	public:
		Gizmo() = default;

		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Draw3D() override;
		void Draw2D() override;

		void Update() override;

		~Gizmo();
	};
}