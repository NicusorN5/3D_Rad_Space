#include "Model3D.hpp"
#include "../../Core/Logging/Exception.hpp"
#include "../../Core/Logging/AssetLoadingError.hpp"
#include "../ShaderManager.hpp"
#include "../../Internal/AssetUUIDReader.hpp"

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

Assimp::Importer importer;

Model3D::Model3D(Internal::AssetUUIDReader) : 
	_device(nullptr)
{
}

Model3D::Model3D(GraphicsDevice* Device, const std::filesystem::path& path) :
	_device(Device)
{
	//basicTexturedNBT = std::make_unique<Shaders::BasicTextured>(Device);
	auto basicTexturedNBT = ShaderManager::LoadShader<Shaders::BasicTextured>(Device);

	if (!std::filesystem::exists(path)) throw AssetLoadingError(Tag<Model3D>{}, path, "This file doesn't exist!");

	const aiScene* scene = importer.ReadFile(path.string(),
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_SplitLargeMeshes |
		aiProcess_SortByPType |
		aiProcess_GenBoundingBoxes |
#if USING_DX11
		aiProcess_FlipUVs |
		aiProcess_FlipWindingOrder
#endif
	);

	if(scene == nullptr)
		throw AssetLoadingError(Tag<Model3D>{}, path, importer.GetErrorString());
	if(!scene->HasMeshes())
		throw AssetLoadingError(Tag<Model3D>{}, path, "The scene doesn't contain any models!");
	
	//loop meshes
	std::vector<std::unique_ptr<ModelMeshPart>> meshParts;
	for (unsigned i = 0, k =0; i < scene->mNumMeshes; i++) 
	{
		//validate current mesh
		if (!scene->mMeshes[i]->HasFaces())
		{
			continue;
		}
		if (!scene->mMeshes[i]->HasPositions())
		{
			continue;
		}

		//Create index buffer
		std::vector<unsigned> indices;
		for (unsigned j = 0; j < scene->mMeshes[i]->mNumFaces; j++) //loop faces
		{
			unsigned numIndices = scene->mMeshes[i]->mFaces[j].mNumIndices;
			if (numIndices < 3) continue; //skip lines and points

			unsigned* face = scene->mMeshes[i]->mFaces[j].mIndices;

			indices.insert(indices.end(), face, face + numIndices);
		}

		//Find the vertex buffer type
		int numVertexColors = scene->mMeshes[i]->GetNumColorChannels();
		bool hasNormals = scene->mMeshes[i]->HasNormals();
		bool hasBitangents = scene->mMeshes[i]->HasTangentsAndBitangents();
		int numUVMaps = scene->mMeshes[i]->GetNumUVChannels();

		size_t structSize = sizeof(Vector3) * 4; //position + normal + tangent + bitangent
		if (numUVMaps == 1) structSize += sizeof(Vector2);
		if (numVertexColors == 1) structSize += sizeof(Color);

		//create the vertex buffer
		unsigned numVerts = scene->mMeshes[i]->mNumVertices;
		std::vector<float> vertices;

		if (hasNormals && hasBitangents)
		{
			for (unsigned j = 0; j < numVerts; j++) //Copy vertices
			{
				auto position = scene->mMeshes[i]->mVertices[j];
				vertices.insert(vertices.end(), {position.x, position.y, position.z});

				auto normal = scene->mMeshes[i]->mNormals[j];
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });

				auto tangent = scene->mMeshes[i]->mTangents[j];
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });

				auto bitangent = scene->mMeshes[i]->mBitangents[j];
				vertices.insert(vertices.end(), { bitangent.x, bitangent.y, bitangent.z });

				if (numUVMaps == 1)
				{
					auto uv = scene->mMeshes[i]->mTextureCoords[0][j];
					vertices.insert(vertices.end(), { uv.x, uv.y });
				}

				if (numVertexColors == 1)
				{
					auto color = scene->mMeshes[i]->mColors[0][j];
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });
				}
			}
		}

		if(vertices.empty() || indices.empty())
		{
			meshParts.push_back(nullptr);
			continue;
		}

		auto mesh = std::make_unique<ModelMeshPart>(Device, basicTexturedNBT, &vertices[0], numVerts, structSize, indices);
		
		//determine bounding box and sphere
		auto aabbMin = scene->mMeshes[i]->mAABB.mMin;
		auto aabbMax = scene->mMeshes[i]->mAABB.mMax;
		mesh->_box = BoundingBox(
			Vector3(aabbMin.x, aabbMin.y, aabbMin.z),
			Vector3(aabbMax.x - aabbMin.x, aabbMax.y - aabbMin.y, aabbMax.z - aabbMin.z)
		);
		mesh->_sphere = BoundingSphere(mesh->_box);
		std::unique_ptr<Texture2D> diffuseTexture;

		if(numUVMaps == 1)
		{
			int materialindex = scene->mMeshes[i]->mMaterialIndex;
			aiString texturePath;
			aiReturn r = scene->mMaterials[materialindex]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
			if(r == aiReturn_SUCCESS)
			{
				std::filesystem::path p(path); //get the current path of the model
				p.remove_filename(); //remove the model filename 
				p += texturePath.C_Str(); //concatenate the texture path.

				diffuseTexture = std::make_unique<Texture2D>(Device, p.string());
			}
			else
			{
				aiColor3D color;
				r = scene->mMaterials[materialindex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
				if(r == aiReturn_SUCCESS)
				{
					float opacity = 1.0f;
					scene->mMaterials[materialindex]->Get(AI_MATKEY_OPACITY, opacity);

					std::array<Color, 4> tColors;
					tColors.fill(Color(color.r, color.g, color.b, opacity));

					diffuseTexture = std::make_unique<Texture2D>(Device, tColors, 2, 2);
				}
				else
				{
					std::array<Color, 4> tColors;
					tColors.fill(Colors::White);

					diffuseTexture = std::make_unique<Texture2D>(Device, tColors, 2, 2);
				}
			}
		}

		mesh->Textures.push_back(std::move(diffuseTexture));
		mesh->TextureSamplers.push_back(std::make_unique<SamplerState>(Device));
		meshParts.push_back(std::move(mesh));
	}

	//generate node structure
	unsigned numChildren = scene->mRootNode->mNumChildren;

	if(numChildren != 0)
	{
		_meshes.reserve(numChildren);

		for(unsigned i = 0; i < numChildren; i++)
		{
			_processNode(meshParts, scene->mRootNode->mChildren[i]);
		}
	}
	else
	{
		_meshes.push_back(std::make_unique<ModelMesh>(meshParts));
	}

	if(_meshes.size() == 0)
	{
		_box = BoundingBox(Vector3(0, 0, 0), Vector3(0, 0, 0));
		_sphere = BoundingSphere(Vector3(0, 0, 0), 0);
		return;
	}

	_box = _meshes[0]->GetBoundingBox();
	_sphere = _meshes[0]->GetBoundingSphere();

	for (size_t i = 1; i < _meshes.size(); i++)
	{
		_box = BoundingBox(_box, _meshes[i]->GetBoundingBox());
		_sphere = BoundingSphere(_sphere, _meshes[i]->GetBoundingSphere());
	}
}

void Model3D::_processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts, void* currentNode)
{
	if (currentNode == nullptr) return;
	if(parts.empty()) return;

	auto node = static_cast<aiNode*>(currentNode);
	
	if(node->mNumMeshes == 0) return;

	std::vector<std::unique_ptr<ModelMeshPart>> lparts;
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		if(parts[node->mMeshes[i]] == nullptr) continue;

		lparts.push_back(std::move(parts[node->mMeshes[i]]));
		lparts[i]->Transform = Matrix4x4(reinterpret_cast<float*>(&node->mTransformation));
	}
	_meshes.push_back(std::make_unique<ModelMesh>(lparts));

	for (unsigned i = 0; i < node->mNumChildren; i++)
	{
		_processNode(parts, node->mChildren[i]);
	}
}

void Model3D::SetTransform(const Matrix4x4&m)
{
	for(const auto &mesh : _meshes)
	{
		for(auto &meshPart : *mesh.get())
		{
			meshPart->Transform = m;
		}
	}
}

void Model3D::Draw()
{
	for (auto& mesh :_meshes)
	{
		mesh->Draw();
	}
}

void Model3D::Draw(const Matrix4x4&m)
{
	for(auto &mesh : _meshes)
	{
		for(auto &meshPart : *mesh.get())
		{
			meshPart->Transform = m;
			meshPart->Draw();
		}
	}
}

Model3D::iterator Model3D::begin()
{
	return _meshes.begin();
}

Model3D::iterator Model3D::end()
{
	return _meshes.end();
}

size_t Model3D::NumMeshes()
{
	return _meshes.size();
}

BoundingBox Model3D::GetBoundingBox() const noexcept
{
	return _box;
}

BoundingSphere Model3D::GetBoundingSphere() const noexcept
{
	return _sphere;
}

void Model3D::SetShader(std::shared_ptr<Shaders::Effect> effect)
{
	for (auto& mesh : _meshes)
	{
		for (auto& meshPart : *mesh.get())
		{
			meshPart->SetShaders(effect);
		}
	}
}

void Model3D::SetShaders(std::span<std::shared_ptr<Shaders::Effect>> effects)
{
	size_t i = 0;
	size_t len = effects.size();

	for (auto const& mesh : _meshes)
	{
		for (auto const& meshPart : *mesh.get())
		{
			if (i < len)
				meshPart->SetShaders(effects[i++]);
			else return;
		}
	}
}

void Model3D::DrawEffect(Shaders::Effect *effect)
{
	for (auto& mesh : _meshes)
	{
		for (auto& meshPart : *mesh.get())
		{
			meshPart->Draw(effect);
		}
	}
}

void Model3D::DrawEffect(Shaders::Effect* effect, const Math::Matrix4x4& mvp)
{
	for(auto &mesh : _meshes)
	{
		for(auto &meshPart : *mesh.get())
		{
			meshPart->Transform = mvp;
			meshPart->Draw(effect);
		}
	}
}

Reflection::UUID Model3D::GetUUID() const noexcept
{
	// {A405951A-7454-4A03-868C-1D2022D43F45}
	return { 0xa405951a, 0x7454, 0x4a03, { 0x86, 0x8c, 0x1d, 0x20, 0x22, 0xd4, 0x3f, 0x45 } };
}

const char* Model3D::FileExtension() const noexcept
{
	return  "All supported mesh files (*.3ds;*.3mf;*.dae;*.fbx;*.gltf;*.glb;*.obj;*.x)\0*.3ds;*.3mf;*.dae;*.fbx;*.gltf;*.glb;*.obj;*.x\0"
			"Autodesk 3ds Max Model (*.3ds)\0*.3ds\0"
			"3D Manufacturing Format(*.3mf)\0*.3mf\0"
			"COLLADA Model (*.dae)\0*.dae\0"
			"Filmbox (FBX) Mesh (*.fbx)\0*.fbx\0"
			"Graphics Library Transmission Format(glTF) (*.gltf;*.glb)\0*.gltf;*.glb\0"
			"Wavefront OBJ (*.obj)\0*.obj\0"
			"DirectX Mesh (*.x)\0*.x\0"
			"All Files(*.*)\0*.*\0\0";
}

ModelMesh* Model3D::operator[](unsigned i)
{
	return _meshes.at(i).get();
}
