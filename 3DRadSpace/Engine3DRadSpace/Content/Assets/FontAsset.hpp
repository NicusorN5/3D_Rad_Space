#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class IGraphicsDevice;
		class Font;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT FontAsset final : public IAsset
		{
			std::unique_ptr<Graphics::Font> _font;
		public:
			FontAsset(IGraphicsDevice* device, const std::filesystem::path &path);

			/// <summary>
			/// UUID of the Font type. Used internally.
			/// </summary>
			/// <returns>UUID</returns>
			Reflection::UUID GetUUID() const noexcept override;
			/// <summary>
			/// Supported file types, used internally.
			/// </summary>
			/// <returns></returns>
			const char* FileExtension() const noexcept override;
		};
	}
}
