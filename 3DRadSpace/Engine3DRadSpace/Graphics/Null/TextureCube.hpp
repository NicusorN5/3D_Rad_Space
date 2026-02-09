#pragma once
#include "../ITextureCube.hpp"
#include "../ITexture2D.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;
	class TextureCube : public ITextureCube
	{
	public:
		TextureCube(GraphicsDevice* device, const std::filesystem::path& filePath);
		TextureCube(GraphicsDevice* device, std::array<ITexture2D*, 6> cubeMap);

		Math::UPoint Size() const noexcept override;
		unsigned Width() const noexcept override;
		unsigned Height() const noexcept override;

		void* GetViewHandle() const noexcept override;
		std::unique_ptr<ITextureCube> CreateStaging() override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;
	};
}