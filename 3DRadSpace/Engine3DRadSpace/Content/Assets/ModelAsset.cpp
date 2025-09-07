#include "ModelAsset.hpp"
#include "../../Graphics/Model3D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;

ModelAsset::ModelAsset(IGraphicsDevice* device, const std::filesystem::path & path) :
	_font(new Model3D(device, path))
{
}

Reflection::UUID ModelAsset::GetUUID() const noexcept
{
	// {A405951A-7454-4A03-868C-1D2022D43F45}
	return {0xa405951a, 0x7454, 0x4a03, { 0x86, 0x8c, 0x1d, 0x20, 0x22, 0xd4, 0x3f, 0x45 }};
}

const char* ModelAsset::FileExtension() const noexcept
{
	return  "All supported mesh files (*.3ds;*.3mf;*.dae;*.fbx;*.gltf;*.glb;*.obj;*.x)\0*.3ds;*.3mf;*.dae;*.fbx;*.gltf;*.glb;*.obj;*.x\0"
		"Autodesk 3ds Max Model (*.3ds)\0*.3ds\0"
		"3D Manufacturing Format(*.3mf)\0*.3mf\0"
		"COLLADA Model (*.dae)\0*.dae\0"
		"Filmbox (FBX) Mesh (*.fbx)\0*.fbx\0"
		"GL Transmission Format(glTF) (*.gltf;*.glb)\0*.gltf;*.glb\0"
		"Wavefront OBJ (*.obj)\0*.obj\0"
		"DirectX Mesh (*.x)\0*.x\0"
		"All Files(*.*)\0*.*\0\0";
}