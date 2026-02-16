#pragma once
#include "IPrimitive.hpp"
#include "../ITextureCube.hpp"

namespace Engine3DRadSpace::Objects
{
	class Camera;
}

namespace Engine3DRadSpace::Content::Assets
{
	class SkyboxAsset;
}

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Inverted Box primitive used primarly for skyboxes.
	/// </summary>
	/// <remarks>
	/// This doesn't inherit IPrimitive - since this renders a textured mesh.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT CubeMapSkybox final : public IPrimitive
	{
		std::unique_ptr<ITextureCube> _texture;

		void _compileShader(IShaderCompiler* compiler);
		void _create();

		CubeMapSkybox(std::nullptr_t);
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
		CubeMapSkybox(IGraphicsDevice* device, std::array<ITexture2D*, 6> &faces);

		/// <summary>
		/// Creates a new instance of the CubeMapSkybox class.
		/// </summary>
		/// <param name="device">Graphics device</param>
		/// <param name="dds">Cubemap DDS image</param>
		CubeMapSkybox(IGraphicsDevice* device, const std::filesystem::path& dds);

		CubeMapSkybox(CubeMapSkybox&&) noexcept = default;
		CubeMapSkybox& operator=(CubeMapSkybox&&) noexcept = default;

		static std::array<VertexPosition, 8> CreateVertices();
		static std::array<unsigned, 36> CreateIndices();

		void Draw3D() override;
		
		~CubeMapSkybox() override = default;

		friend class Engine3DRadSpace::Content::Assets::SkyboxAsset;
	};
}