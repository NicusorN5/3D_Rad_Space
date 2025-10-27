#pragma once
#include "../../Graphics/Primitives/CubeMapSkybox.hpp"
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	class E3DRSP_CONTENT_ASSETS_EXPORT SkyboxAsset : public IAsset
	{
		Graphics::Primitives::CubeMapSkybox _skybox;
		Graphics::Primitives::CubeMapSkybox _loadCubeMap(Graphics::IGraphicsDevice *device, const std::filesystem::path& path);

		SkyboxAsset(Internal::AssetUUIDReader dummy);
	public:
		SkyboxAsset(IService *device, const std::filesystem::path& path);

		SkyboxAsset(SkyboxAsset&&) noexcept = default;
		SkyboxAsset& operator=(SkyboxAsset&&) noexcept = default;

		Graphics::Primitives::CubeMapSkybox& GetSkybox() noexcept;
		Graphics::Primitives::CubeMapSkybox* operator->() noexcept;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;
		std::type_index InitializationService() const noexcept override;

		friend class Internal::AssetUUIDReader;
	};
}