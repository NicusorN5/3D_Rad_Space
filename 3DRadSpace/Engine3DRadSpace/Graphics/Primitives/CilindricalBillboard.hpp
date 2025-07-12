#pragma once
#include "../ModelMeshPart.hpp"
#include "../../Objects/IDrawable3D.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	class E3DRSP_GRAPHICS_EXPORT CilindricalBillboard : public IDrawable3D
	{
		GraphicsDevice *_device;
		std::unique_ptr<ModelMeshPart> _plane;

		virtual Math::Matrix4x4 _mvp() const noexcept;
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
	
		Math::Vector3 Position;
		Math::Vector2 Scale = Math::Vector2::One();
		Math::Vector3 Axis = Math::Vector3::UnitY();
	
		Texture2D* Texture;

		static std::array<VertexPositionUV, 4> CreateVertices();

		void Draw3D() override;
	};
}