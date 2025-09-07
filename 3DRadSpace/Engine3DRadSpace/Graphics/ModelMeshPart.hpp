#pragma once
#include "IVertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "VertexDeclarations.hpp"
#include "Effect.hpp"
#include "../Math/BoundingSphere.hpp"
#include "../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D;

	/// <summary>
	/// Represents a mesh formed by a index and vertex buffer, plus an effect.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ModelMeshPart
	{
		GraphicsDevice* _device;

		std::shared_ptr<Shaders::Effect> _shaders;

		Math::BoundingBox _box;
		Math::BoundingSphere _sphere;

		std::unique_ptr<IVertexBuffer> _stagingVertex;
		std::unique_ptr<IIndexBuffer> _stagingIndex;
	public:
		std::unique_ptr<IIndexBuffer> IndexBuffer;
		std::unique_ptr<IVertexBuffer> VertexBuffer;

		ModelMeshPart(
			std::shared_ptr<Shaders::Effect> shaders,
			Graphics::IVertexBuffer* vert, 
			Graphics::IIndexBuffer* buffer
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
		std::vector<std::unique_ptr<ITexture2D>> Textures;
		std::vector<std::unique_ptr<ISamplerState>> TextureSamplers;

		void Draw();
		void Draw(Shaders::Effect* effect);

		Math::BoundingBox GetBoundingBox() const noexcept;
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		Graphics::IVertexBuffer* GetVertexBuffer() const noexcept;
		Graphics::IIndexBuffer* GetIndexBuffer() const noexcept;

		Shaders::Effect* GetShaders() const noexcept;
		void SetShaders(std::shared_ptr<Shaders::Effect> shaders);

		/// <summary>
		/// Creates staging vertex and index buffers available for CPU reading if they don't exist. If they already exist, returns the already created buffers.
		/// </summary>
		/// <returns>Pair of vertex and index buffers pointer references</returns>
		std::pair<Graphics::IVertexBuffer*, Graphics::IIndexBuffer*> CreateStagingBuffers();

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

