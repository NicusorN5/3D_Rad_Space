#pragma once
#include "../ModelMeshPart.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Inverted Box primitive used primarly for skyboxes.
	/// </summary>
	/// <remarks>
	/// This doesn't inherit IPrimitive - since this renders a textured mesh.
	/// </remarks>
	class CubeMapSkybox final
	{
		std::array<Texture2D, 6> _faces;

		std::unique_ptr<ModelMeshPart> _skyboxMesh;
	public:
		/// <summary>
		/// Constructs a new instance of the CubeMapSkybox class.
		/// </summary>
		/// <param name="device">Graphics device used to create a cubemap index and vertex buffers.</param>
		/// <param name="faces">Texture faces ordered in pos-neg xyz pairs.</param>
		/// 
		/// <remarks>
		///		Faces are ordered in positive-negative XYZ pairs. To be exact:
		///		1 - Positive X - PX
		///		2 - Negative X - NX
		///		3 - Positive Y - PY
		///		4 - Negative Y - NY
		///     5 - Positive Z - PZ
		///		6 - Negative Z - NZ
		/// </remarks>
		CubeMapSkybox(GraphicsDevice* device, std::array<Texture2D,6> &&faces);
	};
}