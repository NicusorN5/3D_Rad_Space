#pragma once
#include "../IAsset.hpp"
#include "../../Graphics/ShaderFeatureLevel.hpp"

namespace Engine3DRadSpace
{
	namespace Graphics
	{
		class IGraphicsDevice;
		class IShaderCompiler;
		class Effect;
	}
	namespace Internal
	{
		struct AssetUUIDReader;
	}

	namespace Content::Assets
	{
		class E3DRSP_CONTENT_ASSETS_EXPORT EffectAsset : public IAsset
		{
			IGraphicsDevice* _device;
			std::unique_ptr<Effect> _effect;

			ShaderAsset(Internal::AssetUUIDReader dummy);

			std::array<ShaderDescFile, 5> _createDesc(
				const std::filesystem::path& path,
				ShaderFeatureLevel featureLevel
			);
		public:
			ShaderAsset(
				IService* device, 
				const std::filesytem::path& path,
				ShaderFeatureLevel featureLevel = ShaderFeatureLevel::DX_V4
			);

			ShaderAsset(NullAsset&&) noexcept = default;
			ShaderAsset& operator=(NullAsset&&) noexcept = default;

			Reflection::UUID GetUUID() const noexcept override;
			const char* FileExtension() const noexcept override;
			std::type_index InitializationService() const noexcept override;

			Effect* operator->() const noexcept;
			Effect& operator() noexcept;

			friend class Internal::AssetUUIDReader;

			~ShaderAsset() override = default;
		};
	}
}