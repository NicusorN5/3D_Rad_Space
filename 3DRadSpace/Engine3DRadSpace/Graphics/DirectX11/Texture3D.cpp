#include "Texture3D.hpp"
#include "PixelFormat.hpp"
#include "GraphicsDevice.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;

Texture3D::Texture3D(GraphicsDevice* device, std::span<Texture2D*> textures) :
	_device(device)
{
	assert(device != nullptr);
	assert(textures.size() > 0);

	_size.Z = textures.size();
	_size.X = textures[0]->Width();
	_size.Y = textures[0]->Height();

	std::vector<ID3D11Texture2D*> textureHandles;
	for(size_t i = 1; i < textures.size(); i++)
	{
		//Textures that don't match the initial size are skipped.
		if(_size.X != textures[i]->Width()) continue;
		if(_size.Y != textures[i]->Height()) continue;

		textureHandles[i] = static_cast<ID3D11Texture2D*>(textures[i]->GetHandle());
	}

	D3D11_TEXTURE3D_DESC desc{};
	desc.Width = _size.X;
	desc.Height = _size.Y;
	desc.Depth = static_cast<UINT>(_size.Z);
	desc.Format = PixelFormat_ToDX11(textures[0]->Format());
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	device->_device->CreateTexture3D(& desc, nullptr, & _texture);

	_texture->GetDesc(&desc);
	auto mipCount = desc.MipLevels;

	for(UINT face = 0; face < 6; ++face)
	{
		for(UINT mip = 0; mip < mipCount; ++mip)
		{
			UINT dstSubresource = D3D11CalcSubresource(mip, face, mipCount);
			UINT srcSubresource = D3D11CalcSubresource(mip, 0, mipCount);
			_device->_context->CopySubresourceRegion(
				_texture.Get(),
				dstSubresource,
				0,
				0,
				0,
				textureHandles[face],
				srcSubresource,
				nullptr
			);
		}
	}

	device->_device->CreateShaderResourceView(_texture.Get(), nullptr, &_srv);
}

Texture3D::Texture3D(GraphicsDevice* device, Microsoft::WRL::ComPtr<ID3D11Texture3D>&& texture, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv) :
	_device(device),
	_texture(std::move(texture)),
	_srv(std::move(srv))
{
}

void Texture3D::_setDebugInfo()
{
#ifdef _DEBUG
	const char textureName[] = "ITextureCube::_texture";
	_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureName) - 1, textureName);
	const char srvName[] = "ITextureCube::_resourceView";
	_srv->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(srvName) - 1, srvName);
#endif
}

Math::UPoint3 Texture3D::Size() const noexcept
{
	return _size;
}

unsigned Texture3D::Width() const noexcept
{
	return _size.X;
}

unsigned Texture3D::Height() const noexcept
{
	return _size.Y;
}

unsigned Texture3D::Depth() const noexcept
{
	return _size.Z;
}

void* Texture3D::GetViewHandle() const noexcept
{
	return _srv.Get();
}

[[nodiscard]] std::unique_ptr<ITexture3D> Texture3D::CreateStaging()
{
	D3D11_TEXTURE3D_DESC desc;
	_texture->GetDesc(&desc);

	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

	Microsoft::WRL::ComPtr<ID3D11Texture3D> stagingTexture;

	HRESULT r = _device->_device->CreateTexture3D(&desc, nullptr, &_texture);
	if(FAILED(r)) throw Logging::Exception("CreateTexture3D failed!");

	_device->_context->CopyResource(stagingTexture.Get(), _texture.Get());

	return std::make_unique<Texture3D>(std::move(Texture3D(_device, std::move(stagingTexture), {})));
}

size_t Texture3D::ReadData(size_t subResource, void** data)
{
	if(data == nullptr) return 0;

	D3D11_MAPPED_SUBRESOURCE res;
	_device->_context->Map(_texture.Get(), subResource, D3D11_MAP_WRITE, 0, &res);

	*data = res.pData;
	return res.RowPitch;
}

void Texture3D::SetData(size_t subResource, void* data, size_t buffSize)
{
	if(data == nullptr || buffSize == 0) return;

	D3D11_MAPPED_SUBRESOURCE res;
	_device->_context->Map(_texture.Get(), subResource, D3D11_MAP_WRITE, 0, &res);
}
void Texture3D::EndRead(size_t subResource)
{
	_device->_context->Unmap(_texture.Get(), subResource);
}

void* Texture3D::GetHandle() const noexcept
{
	return _texture.Get();
}

IGraphicsDevice* Texture3D::GetGraphicsDevice() const noexcept
{
	return _device;
}