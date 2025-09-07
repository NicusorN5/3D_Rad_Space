#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class IGraphicsDevice;
		class Model3D;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT ModelAsset final : public IAsset
		{
			std::unique_ptr<Graphics::Model3D> _font;
		public:
			ModelAsset(IGraphicsDevice* device, const std::filesystem::path &path);

			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Refer to https://github.com/assimp/assimp/blob/master/doc/Fileformats.md for all supported file formats.
			/// </summary>
			/// <returns></returns>
			const char* FileExtension() const noexcept override;
		};
	}
}
