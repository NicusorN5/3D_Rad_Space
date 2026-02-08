#pragma once
#include "GraphicsDevice.hpp"
#include "../ITexture1D.hpp"
#include "../PixelFormat.hpp"
#include "../Math/Color.hpp"

namespace Engine3DRadSpace::Graphics::DirectX11
{
	class E3DRSP_GRAPHICS_DX11_EXPORT Texture1D : public ITexture1D
	{
	private:
		GraphicsDevice* _device;
		Microsoft::WRL::ComPtr<ID3D11Texture1D> _texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
		PixelFormat _format;
		size_t _size;

		void _setDebugInfo();
		void _createSRV();
		
		Texture1D(GraphicsDevice* device, D3D11_TEXTURE1D_DESC* desc, Microsoft::WRL::ComPtr<ID3D11Texture1D>&& texture);
	public:
		Texture1D(GraphicsDevice* device, size_t numElements, PixelFormat format );
		Texture1D(GraphicsDevice* device, std::span<Math::Color> colors);

		Texture1D(const Texture1D&) = delete;
		Texture1D(Texture1D&&) noexcept = default;

		Texture1D& operator=(const Texture1D&) = delete;
		Texture1D& operator=(Texture1D&&) noexcept = default;

		size_t Length() const noexcept override;
		void* GetViewHandle() const noexcept override;
		[[nodiscard]] std::unique_ptr<ITexture1D> CreateStaging() override;

		size_t ReadData(void** data) override;
		void SetData(void* data, size_t buffSize) override;
		void EndRead() override;

		void* GetHandle() const noexcept override;
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~Texture1D() override = default;

		friend class GraphicsDevice;
		friend class GraphicsCommandList;

		friend class VertexShader;
		friend class FragmentShader;
		friend class HullShader;
		friend class DomainShader;
		friend class GeometryShader;
		friend class DepthStencilBuffer;
	};
}