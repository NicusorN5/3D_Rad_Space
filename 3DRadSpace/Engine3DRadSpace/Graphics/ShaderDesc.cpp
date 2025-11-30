#include "ShaderDesc.hpp"

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