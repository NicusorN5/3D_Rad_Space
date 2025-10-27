#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace
{
	class IService;
	namespace Graphics
	{
		class Model3D;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT ModelAsset final : public IAsset
		{
			std::unique_ptr<Graphics::Model3D> _font;
		public:
			ModelAsset(IService* device, const std::filesystem::path &path);

			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Refer to https://github.com/assimp/assimp/blob/master/doc/Fileformats.md for all supported file formats.
			/// </summary>
			/// <returns></returns>
			const char* FileExtension() const noexcept override;

			std::type_index InitializationService() const noexcept override;
		};
	}
}
