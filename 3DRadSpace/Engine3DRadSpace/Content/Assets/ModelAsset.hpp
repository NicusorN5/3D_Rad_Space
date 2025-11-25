#pragma once
#include "IAssetWrapper.hpp"
#include "../../Graphics/Model3D.hpp"

namespace Engine3DRadSpace
{
	class IService;
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT ModelAsset final : public IAssetWrapper<Graphics::Model3D>
		{
			ModelAsset(Internal::AssetUUIDReader dummy);
		public:
			ModelAsset(IService* device, const std::filesystem::path &path);

			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Refer to https://github.com/assimp/assimp/blob/master/doc/Fileformats.md for all supported file formats.
			/// </summary>
			/// <returns></returns>
			const char* FileExtension() const noexcept override;

			std::type_index InitializationService() const noexcept override;

			~ModelAsset() override = default;

			friend struct Internal::AssetUUIDReader;
		};
	}
}