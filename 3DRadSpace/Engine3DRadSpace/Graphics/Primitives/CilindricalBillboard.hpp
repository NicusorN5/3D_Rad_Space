#pragma once
#include "../ModelMeshPart.hpp"
#include "../../Objects/IDrawable3D.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_EXPORT CilindricalBillboard : public IDrawable3D
	{
		GraphicsDevice *_device;
		std::unique_ptr<ModelMeshPart> _plane;

		Math::Matrix4x4 _mvp() const noexcept;
	public:
		CilindricalBillboard(GraphicsDevice* device);

		/// <summary>
		/// Camera view matrix.
		/// </summary>
		Math::Matrix4x4 View;
		/// <summary>
		/// Camera projection matrix.
		/// </summary>
		Math::Matrix4x4 Projection;
		/// <summary>
		/// World transform, composed usually of Scale, Rotation, Translation.
		/// </summary>
		Math::Matrix4x4 Transform;

		Texture2D* Texture;

		static std::array<VertexPositionUV, 4> CreateVertices();

		void Draw3D() override;
	};
}