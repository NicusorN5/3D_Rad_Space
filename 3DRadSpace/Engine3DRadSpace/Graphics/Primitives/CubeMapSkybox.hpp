#pragma once
#include "../ModelMeshPart.hpp"
#include "../../IDrawable3D.hpp"

namespace Engine3DRadSpace::Objects
{
	class Camera;
}

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Inverted Box primitive used primarly for skyboxes.
	/// </summary>
	/// <remarks>
	/// This doesn't inherit IPrimitive - since this renders a textured mesh.
	/// </remarks>
	class DLLEXPORT CubeMapSkybox final : public IDrawable3D
	{
		std::array<std::unique_ptr<ModelMeshPart>, 6> _faces;
	public:
		/// <summary>
		/// Constructs a new instance of the CubeMapSkybox class.
		/// </summary>
		/// <param name="device">Graphics device used to create a cubemap index and vertex buffers.</param>
		/// <param name="faces">Texture faces ordered in pos-neg xyz pairs.</param>
		/// 
		/// <remarks>
		///		Faces are ordered in positive-negative XYZ pairs. To be precise:
		///		1 - Positive X - PX
		///		2 - Negative X - NX
		///		3 - Positive Y - PY
		///		4 - Negative Y - NY
		///     5 - Positive Z - PZ
		///		6 - Negative Z - NZ
		/// </remarks>
		CubeMapSkybox(GraphicsDevice* device, std::array<Texture2D,6> &&faces);

		/// <summary>
		/// Model/world transform for this primitive. Usually only made of scale and translation(camera position). 
		/// </summary>
		Math::Matrix4x4 Model = Math::Matrix4x4();
		/// <summary>
		/// Camera view matrix.
		/// </summary>
		Math::Matrix4x4 View = Math::Matrix4x4();
		/// <summary>
		/// Camera projection matrix.
		/// </summary>
		Math::Matrix4x4 Projection = Math::Matrix4x4();

		void SetTransformFromCamera(const Objects::Camera& camera);

		void Draw3D() override;
	};
}