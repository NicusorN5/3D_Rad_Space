#pragma once
#include "../../Graphics/Primitives/CubeMapSkybox.hpp"
#include "IAssetWrapper.hpp"
#include "../../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	class E3DRSP_CONTENT_ASSETS_EXPORT SkyboxAsset : public IAssetWrapper<Graphics::Primitives::CubeMapSkybox>
	{
		Graphics::Primitives::CubeMapSkybox _loadCubeMap(Graphics::IGraphicsDevice *device, const std::filesystem::path& path);

		SkyboxAsset(Internal::AssetUUIDReader dummy);
	public:
		SkyboxAsset(IService *device, const std::filesystem::path& path);

		SkyboxAsset(SkyboxAsset&&) noexcept = default;
		SkyboxAsset& operator=(SkyboxAsset&&) noexcept = default;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;
		std::type_index InitializationService() const noexcept override;

		~SkyboxAsset() override = default;

		friend class Internal::AssetUUIDReader;
	};
}