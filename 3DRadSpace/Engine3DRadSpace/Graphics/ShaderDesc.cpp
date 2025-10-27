#include "ShaderDesc.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

ShaderDesc::ShaderDesc(
	const std::string& EntryPoint,
	ShaderType type,
	ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
) :
	EntryPoint(EntryPoint),
	Type(type),
	FeatureLevel(FeatureLevel)
{
}

ShaderDescFromFile::ShaderDescFromFile(
	std::filesystem::path FilePath,
	const std::string& EntryPoint,
	ShaderType type,
	ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
) : 
	ShaderDesc(EntryPoint, type, FeatureLevel),
	FilePath(std::move(FilePath))
{
}

ShaderDescFromSource::ShaderDescFromSource(
	const std::string& SourceCode,
	const std::string& EntryPoint,
	ShaderType type,
	ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
) : 
	ShaderDesc(EntryPoint, type, FeatureLevel),
	SourceCode(SourceCode)
{
}