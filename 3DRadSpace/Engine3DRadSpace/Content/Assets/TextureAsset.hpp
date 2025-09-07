#pragma once
#include "../IAsset.hpp"
#include "../../Graphics/IGraphicsDevice.hpp"
#include "../../Graphics/ITexture2D.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	class E3DRSP_CONTENT_ASSETS_EXPORT TextureAsset final : IAsset
	{
		std::unique_ptr<Graphics::ITexture2D> _texture;
	public:
		TextureAsset(Graphics::IGraphicsDevice* device, const std::filesystem::path &path);

		TextureAsset(const TextureAsset&) = delete;
		TextureAsset(TextureAsset&&) noexcept = default;

		TextureAsset& operator=(const TextureAsset&) = delete;
		TextureAsset& operator=(TextureAsset&&) noexcept = default;

		Reflection::UUID GetUUID() const noexcept override;
		const char* FileExtension() const noexcept override;

		~TextureAsset() override = default;
	};
}