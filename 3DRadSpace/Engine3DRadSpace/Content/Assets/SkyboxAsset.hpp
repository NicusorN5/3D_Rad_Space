#pragma once
#include "../../Graphics/Primitives/CubeMapSkybox.hpp"
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content::Assets
{
	class E3DRSP_CONTENT_EXPORT SkyboxAsset final : public IAsset
	{
		Graphics::Primitives::CubeMapSkybox _skybox;
		Graphics::Primitives::CubeMapSkybox _loadCubeMap(Graphics::GraphicsDevice *device, const std::filesystem::path& path);

		SkyboxAsset(Internal::AssetUUIDReader dummy);
	public:
		SkyboxAsset(Graphics::GraphicsDevice *device, const std::filesystem::path& path);

		Graphics::Primitives::CubeMapSkybox& GetSkybox() noexcept;
		Graphics::Primitives::CubeMapSkybox* operator->() noexcept;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		friend class Internal::AssetUUIDReader;
	};
}