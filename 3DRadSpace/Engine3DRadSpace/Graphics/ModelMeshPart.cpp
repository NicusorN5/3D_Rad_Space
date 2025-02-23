#include "ModelMeshPart.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

ModelMeshPart::ModelMeshPart(
	std::shared_ptr<Effect> shaders,
	Graphics::VertexBuffer *vert, 
	Graphics::IndexBuffer *buffer):
	_device(vert->_device),
	VertexBuffer(vert),
	IndexBuffer(buffer),
	_shaders(shaders)
{
}

ModelMeshPart::ModelMeshPart(GraphicsDevice *Device, std::shared_ptr<Effect> shaders,
	void *vertices, size_t numVerts, size_t structSize, std::span<unsigned> indices):
	_device(Device),
	_shaders(shaders)
{
	VertexBuffer = std::make_unique<Graphics::VertexBuffer>(Device, vertices, structSize, numVerts);
	IndexBuffer = std::make_unique<Graphics::IndexBuffer>(Device, indices);
}

void ModelMeshPart::Draw()
{
	if(_device == nullptr) return;

	_shaders->SetAll();

	for(int i = 0; i < Textures.size(); i++)
	{
		auto vertexShader = _shaders->GetVertexShader();
		if(vertexShader != nullptr)
		{
			vertexShader->SetTexture(i, Textures[i].get());
			vertexShader->SetSampler(i, TextureSamplers[i].get());
			vertexShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto hullShader = _shaders->GetHullShader();
		if(hullShader != nullptr)
		{
			hullShader->SetTexture(i, Textures[i].get());
			hullShader->SetSampler(i, TextureSamplers[i].get());
			hullShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto domainShader = _shaders->GetDomainShader();
		if(domainShader != nullptr)
		{
			domainShader->SetTexture(i, Textures[i].get());
			domainShader->SetSampler(i, TextureSamplers[i].get());
			domainShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto geometryShader = _shaders->GetGeometryShader();
		if(geometryShader != nullptr)
		{
			geometryShader->SetTexture(i, Textures[i].get());
			geometryShader->SetSampler(i, TextureSamplers[i].get());
			geometryShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto pixelShader = _shaders->GetPixelShader();
		if(pixelShader != nullptr)
		{
			pixelShader->SetTexture(i, Textures[i].get());
			pixelShader->SetSampler(i, TextureSamplers[i].get());
			pixelShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}
	}

	_device->SetTopology(VertexTopology::TriangleList);
	_device->DrawVertexBufferWithindices(VertexBuffer.get(), IndexBuffer.get());
}

BoundingSphere ModelMeshPart::GetBoundingSphere() const noexcept
{
	return _sphere;
}

VertexBuffer* ModelMeshPart::GetVertexBuffer() const noexcept
{
	return VertexBuffer.get();
}

IndexBuffer* ModelMeshPart::GetIndexBuffer() const noexcept
{
	return IndexBuffer.get();
}

BoundingBox ModelMeshPart::GetBoundingBox() const noexcept
{
	return _box;
}

Effect *ModelMeshPart::GetShaders() const noexcept
{
	return _shaders.get();
}

void ModelMeshPart::SetShaders(std::shared_ptr<Effect> shaders)
{
	_shaders = shaders;
}

std::pair<Graphics::VertexBuffer*, Graphics::IndexBuffer*> ModelMeshPart::CreateStagingBuffers()
{
	if(!_stagingVertex)
	{
		auto vert = VertexBuffer->CreateStaging();
		_stagingVertex = std::make_unique<Graphics::VertexBuffer>(std::move(vert));
	}
	
	if(!_stagingIndex)
	{
		auto ind = IndexBuffer->CreateStaging();
		_stagingIndex = std::make_unique<Graphics::IndexBuffer>(std::move(ind));
	}

	return std::make_pair<Graphics::VertexBuffer*, Graphics::IndexBuffer*>(
		_stagingVertex.get(),
		_stagingIndex.get()
	);
}
