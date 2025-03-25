#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Effect.hpp"
#include "../Math/BoundingSphere.hpp"
#include "../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a mesh formed by a index and vertex buffer, plus an effect.
	/// </summary>
	class DLLEXPORT ModelMeshPart
	{
		GraphicsDevice* _device;

		std::shared_ptr<Shaders::Effect> _shaders;

		Math::BoundingBox _box;
		Math::BoundingSphere _sphere;

		std::unique_ptr<VertexBuffer> _stagingVertex;
		std::unique_ptr<IndexBuffer> _stagingIndex;
	public:
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexBuffer> VertexBuffer;

		ModelMeshPart(
			std::shared_ptr<Shaders::Effect> shaders,
			Graphics::VertexBuffer* vert, 
			Graphics::IndexBuffer* buffer
		);

		ModelMeshPart(
			GraphicsDevice *Device,
			std::shared_ptr<Shaders::Effect> shaders, 
			void* vertices, 
			size_t numVerts,
			size_t structSize, 
			std::span<unsigned> indices
		);

		ModelMeshPart(ModelMeshPart&& meshPart) noexcept = default;
		ModelMeshPart(ModelMeshPart& meshPart) = delete;

		ModelMeshPart& operator=(ModelMeshPart&) = delete;
		ModelMeshPart& operator=(ModelMeshPart&& meshPart) noexcept = default;

		template<VertexDecl V>
		ModelMeshPart(
			std::shared_ptr<Shaders::Effect> shaders,
			GraphicsDevice* Device,
			std::span<V> vertices,
			std::span<unsigned> indices
		);

		Math::Matrix4x4 Transform = Math::Matrix4x4();
		std::vector<std::unique_ptr<Texture2D>> Textures;
		std::vector<std::unique_ptr<SamplerState>> TextureSamplers;

		void Draw();

		Math::BoundingBox GetBoundingBox() const noexcept;
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		Graphics::VertexBuffer* GetVertexBuffer() const noexcept;
		Graphics::IndexBuffer* GetIndexBuffer() const noexcept;

		Shaders::Effect* GetShaders() const noexcept;
		void SetShaders(std::shared_ptr<Shaders::Effect> shaders);

		/// <summary>
		/// Creates staging vertex and index buffers available for CPU reading if they don't exist. If they already exist, returns the already created buffers.
		/// </summary>
		/// <returns>Pair of vertex and index buffers pointer references</returns>
		std::pair<Graphics::VertexBuffer*, Graphics::IndexBuffer*> CreateStagingBuffers();

		~ModelMeshPart() = default;

		friend class Model3D;
	};

	template<VertexDecl V>
	inline ModelMeshPart::ModelMeshPart(
		std::shared_ptr<Shaders::Effect> shaders,
		GraphicsDevice* Device, std::span<V> vertices, std::span<unsigned> indices ):
		_device(Device),
		_shaders(shaders)
	{
		VertexBuffer = std::make_unique<VertexBufferV<V>>(Device, vertices);
		IndexBuffer = std::make_unique<Graphics::IndexBuffer>(Device, indices);
	}

}

