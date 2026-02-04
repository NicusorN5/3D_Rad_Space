#pragma once
#include "Gizmo.hpp"
#include "../Impl/Camera.hpp"
#include "../../Graphics/Model3D.hpp"
#include "../../Graphics/IRenderTarget.hpp"
#include "../../Graphics/IDepthStencilBuffer.hpp"
#include "../../Graphics/Font.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<Camera> final : public IGizmo
	{
		std::unique_ptr<Graphics::Model3D> _cameraModel;
		std::unique_ptr<Graphics::IRenderTarget> _cameraPreview;
		std::unique_ptr<Graphics::IDepthStencilBuffer> _cameraPreviewDepth;
		std::unique_ptr<Graphics::Font> _font;

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