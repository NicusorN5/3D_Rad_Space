#include "ShaderDesc.hpp"
#include "ShaderDesc.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

ShaderDesc::ShaderDesc(
	const std::string& EntryPoint,
	ShaderType type,
	ShaderFeatureLevel FeatureLevel
) :
	EntryPoint(EntryPoint),
	Type(type),
	FeatureLevel(FeatureLevel)
{
}

ShaderDescFile::ShaderDescFile(
	std::filesystem::path FilePath,
	const std::string& EntryPoint,
	ShaderType type,
	ShaderFeatureLevel FeatureLevel
) : 
	ShaderDesc(EntryPoint, type, FeatureLevel),
	FilePath(std::move(FilePath))
{
}

ShaderDescSource::ShaderDescSource(
	const std::string& SourceCode,
	const std::string& EntryPoint,
	ShaderType type,
	ShaderFeatureLevel FeatureLevel
) : 
	ShaderDesc(EntryPoint, type, FeatureLevel),
	SourceCode(SourceCode)
{
}

E3DRSP_ShaderDesc E3DRSP_ShaderDesc_CreateFromFile(
	const char* filePath,
	const char* entryPoint,
	E3DRSP_ShaderType type,
	E3DRSP_ShaderFeatureLevel featureLevel
)
{
	return new ShaderDescFile(
		std::filesystem::path(filePath),
		std::string(entryPoint),
		static_cast<ShaderType>(type),
		static_cast<ShaderFeatureLevel>(featureLevel)
	);
}

E3DRSP_ShaderDesc E3DRSP_ShaderDesc_CreateFromSource(
	const char* sourceCode,
	const char* entryPoint,
	E3DRSP_ShaderType type,
	E3DRSP_ShaderFeatureLevel featureLevel
)
{
	return new ShaderDescSource(
		std::string(sourceCode),
		std::string(entryPoint),
		static_cast<ShaderType>(type),
		static_cast<ShaderFeatureLevel>(featureLevel)
	);
}

void E3DRSP_ShaderDesc_Destroy(E3DRSP_ShaderDesc shaderDesc)
{
	delete static_cast<ShaderDesc*>(shaderDesc);
}