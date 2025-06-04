#pragma once
#include "../../Graphics/ModelMesh.hpp"
#include "../../Graphics/Shaders/BasicTextured.hpp"
#include "../../Math/BoundingSphere.hpp"
#include "../../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content::Assets
{
	/// <summary>
	/// Represents a 3D model, composed of multiple ModelMesh instances.
	/// </summary>
	/// <remarks>
	/// Assimp is used to load the model.
	/// </remarks>
	class DLLEXPORT Model3D final : public Content::IAsset
	{
		Graphics::GraphicsDevice* _device;
		std::vector<std::unique_ptr<Graphics::ModelMesh>> _meshes;

		void _processNode(std::vector<std::unique_ptr<Graphics::ModelMeshPart>> &parts, void* currentNode);

		Math::BoundingSphere _sphere;
		Math::BoundingBox _box;

		Model3D(Internal::AssetUUIDReader);
	public:
		Model3D(Graphics::GraphicsDevice* Device, const std::filesystem::path& path);

		Model3D(Model3D &) = delete;
		Model3D(Model3D &&) noexcept = default;

		Model3D &operator=(Model3D &) = delete;
		Model3D &operator=(Model3D &&) noexcept = default;

		void SetTransform(const Math::Matrix4x4 &m);

		void Draw();
		void Draw(const Math::Matrix4x4 &mvp);
		
		void DrawEffect(Graphics::Shaders::Effect *effect);
		void DrawEffect(Graphics::Shaders::Effect *effect, const Math::Matrix4x4 &mvp);

		using iterator = std::vector<std::unique_ptr<Graphics::ModelMesh>>::iterator;
		iterator begin();
		iterator end();
		size_t NumMeshes();

		Math::BoundingBox GetBoundingBox() const noexcept;
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		void SetShader(std::shared_ptr<Graphics::Shaders::Effect> effect);
		void SetShaders(std::span<std::shared_ptr<Graphics::Shaders::Effect>> effects);

		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Refer to https://github.com/assimp/assimp/blob/master/doc/Fileformats.md for all supported file formats.
		/// </summary>
		/// <returns></returns>
		const char* FileExtension() const noexcept override;

		~Model3D() = default;

		Graphics::ModelMesh *operator[](unsigned i);
		
		friend struct Internal::AssetUUIDReader;
	};
}