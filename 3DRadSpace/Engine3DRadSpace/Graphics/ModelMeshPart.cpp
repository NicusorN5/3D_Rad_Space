#include "ModelMeshPart.hpp"
#include "Effect.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

ModelMeshPart::ModelMeshPart(
	Graphics::IVertexBuffer *vert, 
	Graphics::IIndexBuffer *index,
	std::shared_ptr<Effect> shaders
):
	_device(vert->GetGraphicsDevice()),
	VertexBuffer(vert),
	IndexBuffer(index),
	_shaders(shaders)
{
}

ModelMeshPart::ModelMeshPart(
	IGraphicsDevice *Device, 
	void *vertices,
	size_t numVerts,
	size_t structSize, 
	std::span<unsigned> indices,
	std::shared_ptr<Effect> shaders
):
	_device(Device),
	_shaders(shaders)
{
	VertexBuffer = Device->CreateVertexBuffer(vertices, structSize, numVerts, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
	IndexBuffer = Device->CreateIndexBuffer(indices);
}

void ModelMeshPart::Draw()
{
	Draw(_shaders.get());
}

void ModelMeshPart::Draw(Effect* effect)
{
	if(_device == nullptr) return;
	if(effect == nullptr) return;

	effect->SetAll();

	for(int i = 0; i < Textures.size(); i++)
	{
		auto vertexShader = effect->GetVertexShader();
		if(vertexShader != nullptr)
		{
			vertexShader->SetTexture(i, Textures[i].get());
			vertexShader->SetSampler(i, TextureSamplers[i].get());
			vertexShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto hullShader = effect->GetHullShader();
		if(hullShader != nullptr)
		{
			hullShader->SetTexture(i, Textures[i].get());
			hullShader->SetSampler(i, TextureSamplers[i].get());
			hullShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto domainShader = effect->GetDomainShader();
		if(domainShader != nullptr)
		{
			domainShader->SetTexture(i, Textures[i].get());
			domainShader->SetSampler(i, TextureSamplers[i].get());
			domainShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto geometryShader = effect->GetGeometryShader();
		if(geometryShader != nullptr)
		{
			geometryShader->SetTexture(i, Textures[i].get());
			geometryShader->SetSampler(i, TextureSamplers[i].get());
			geometryShader->SetData(0, &Transform, sizeof(Matrix4x4));
		}

		auto pixelShader = effect->GetPixelShader();
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

IVertexBuffer* ModelMeshPart::GetVertexBuffer() const noexcept
{
	return VertexBuffer.get();
}

IIndexBuffer* ModelMeshPart::GetIndexBuffer() const noexcept
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

std::pair<IVertexBuffer*, IIndexBuffer*> ModelMeshPart::CreateStagingBuffers()
{
	if(!_stagingVertex)
	{
		_stagingVertex = VertexBuffer->CreateStaging();
	}
	
	if(!_stagingIndex)
	{
		_stagingIndex = IndexBuffer->CreateStaging();
	}

	return std::make_pair<IVertexBuffer*, IIndexBuffer*>(
		_stagingVertex.get(),
		_stagingIndex.get()
	);
}
