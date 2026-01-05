#include "ModelMeshPart.hpp"
#include "ModelMeshPart.h"
#include "Effect.hpp"
#include "../Graphics/IGraphicsCommandList.hpp"
#include "../Math/BoundingBox.h"
#include "../Math/BoundingSphere.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

ModelMeshPart::ModelMeshPart(
	Graphics::IVertexBuffer *vert, 
	Graphics::IIndexBuffer *index,
	Effect* shaders
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
	Effect* shaders
):
	_device(Device),
	_shaders(shaders)
{
	VertexBuffer = Device->CreateVertexBuffer(vertices, structSize, numVerts, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
	IndexBuffer = Device->CreateIndexBuffer(indices);
}

void ModelMeshPart::Draw()
{
	Draw(_shaders);
}

void ModelMeshPart::Draw(Effect* effect)
{
	if(_device == nullptr) return;
	if(effect == nullptr) return;

	effect->SetAll();
	effect->SetData<Math::Matrix4x4>(&Transform, 0, 0);

	for(int i = 0; i < Textures.size(); i++)
	{
		effect->SetTexture(Textures[i].get(), i);
		effect->SetSampler(TextureSamplers[i].get(), i);
	}

	auto cmdList = _device->ImmediateContext();

	cmdList->SetTopology(VertexTopology::TriangleList);
	cmdList->DrawVertexBufferWithindices(VertexBuffer.get(), IndexBuffer.get());
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
	return _shaders;
}

void ModelMeshPart::SetShaders(Effect *shaders)
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

E3DRSP_ModelMeshPart E3DRSP_ModelMeshPart_Create(
	E3DRSP_IGraphicsDevice device,
	void* vertices,
	size_t numVerts,
	size_t structSize,
	unsigned* indices,
	size_t numIndices,
	E3DRSP_Effect shaders
)
{
	return new ModelMeshPart(
		reinterpret_cast<IGraphicsDevice*>(device),
		vertices,
		numVerts,
		structSize,
		std::span<unsigned>(indices, numIndices),
		reinterpret_cast<Effect*>(shaders)
	);
}

E3DRSP_ModelMeshPart E3DRSP_ModelMeshPart_Create2(
	E3DRSP_IVertexBuffer vertexBuffer,
	E3DRSP_IIndexBuffer indexBuffer,
	E3DRSP_Effect shaders
)
{
	return new ModelMeshPart(
		reinterpret_cast<IVertexBuffer*>(vertexBuffer),
		reinterpret_cast<IIndexBuffer*>(indexBuffer),
		reinterpret_cast<Effect*>(shaders)
	);
}

void E3DRSP_ModelMeshPart_Draw(E3DRSP_ModelMeshPart meshPart)
{
	static_cast<ModelMeshPart*>(meshPart)->Draw();
}

void E3DRSP_ModelMeshPart_DrawEffect(E3DRSP_ModelMeshPart meshPart, E3DRSP_Effect effect)
{
	static_cast<ModelMeshPart*>(meshPart)->Draw(reinterpret_cast<Effect*>(effect));
}

E3DRSP_BoundingBox E3DRSP_ModelMeshPart_GetBoundingBox(E3DRSP_ModelMeshPart meshPart)
{
	auto boundingBox = static_cast<ModelMeshPart*>(meshPart)->GetBoundingBox();
	return E3DRSP_BoundingBox{
		{ boundingBox.Position.X, boundingBox.Position.Y, boundingBox.Position.Z },
		{ boundingBox.Scale.X, boundingBox.Scale.Y, boundingBox.Scale.Z }
	};
}

E3DRSP_BoundingSphere E3DRSP_ModelMeshPart_GetBoundingSphere(E3DRSP_ModelMeshPart meshPart)
{
	auto boundingSphere = static_cast<ModelMeshPart*>(meshPart)->GetBoundingSphere();
	return E3DRSP_BoundingSphere{
		{ boundingSphere.Center.X, boundingSphere.Center.Y, boundingSphere.Center.Z },
		boundingSphere.Radius
	};
}

E3DRSP_IVertexBuffer E3DRSP_ModelMeshPart_GetVertexBuffer(E3DRSP_ModelMeshPart meshPart)
{
	return reinterpret_cast<ModelMeshPart*>(meshPart)->GetVertexBuffer();
}

E3DRSP_IIndexBuffer E3DRSP_ModelMeshPart_GetIndexBuffer(E3DRSP_ModelMeshPart meshPart)
{
	return static_cast<ModelMeshPart*>(meshPart)->GetIndexBuffer();
}

E3DRSP_Effect E3DRSP_ModelMeshPart_GetShaders(E3DRSP_ModelMeshPart meshPart)
{
	return static_cast<ModelMeshPart*>(meshPart)->GetShaders();
}

void E3DRSP_ModelMeshPart_SetShaders(E3DRSP_ModelMeshPart meshPart, E3DRSP_Effect shaders)
{
	static_cast<ModelMeshPart*>(meshPart)->SetShaders(reinterpret_cast<Effect*>(shaders));
}

E3DRSP_Matrix4x4 E3DRSP_ModelMeshPart_GetTransform(E3DRSP_ModelMeshPart meshPart)
{
	E3DRSP_Matrix4x4 result;
	auto transform = reinterpret_cast<ModelMeshPart*>(meshPart)->Transform;
	memcpy_s(&result, sizeof(float) * 16, &transform, sizeof(Math::Matrix4x4));

	return result;
}

void E3DRSP_ModelMeshPart_SetTransform(E3DRSP_ModelMeshPart meshPart, const E3DRSP_Matrix4x4 *transform)
{
	memcpy_s(&static_cast<ModelMeshPart*>(meshPart)->Transform, sizeof(Math::Matrix4x4), transform, sizeof(E3DRSP_Matrix4x4));
}

void E3DRSP_ModelMeshPart_Destroy(E3DRSP_ModelMeshPart meshPart)
{
	assert(meshPart != nullptr);
	delete static_cast<ModelMeshPart*>(meshPart);
}