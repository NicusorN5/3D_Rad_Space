#pragma once
#include "Texture2D.hpp"
#include "../ITexture3D.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class E3DRSP_GRAPHICS_EXPORT Texture3D : public ITexture3D
	{
		Texture3D();
		GraphicsDevice* _device;
	public:
		Texture3D(GraphicsDevice* device, std::span<Texture2D*> textures);

		Math::UPoint3 Size() const noexcept override;

		unsigned Width() const noexcept override;
		unsigned Height() const noexcept override;
		unsigned Depth() const noexcept override;

		void* GetViewHandle() const noexcept override;

		size_t ReadData(size_t subResource, void** data) override;
		void SetData(size_t subResource, void* data, size_t buffSize) override;
		void EndRead(size_t subResource) override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		[[nodiscard]] std::unique_ptr<ITexture3D> CreateStaging() override;
	};
}