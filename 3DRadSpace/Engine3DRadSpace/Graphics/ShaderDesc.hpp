#pragma once
#include "../Core/Libs.hpp"
#include "ShaderType.hpp"
#include "ShaderFeatureLevel.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct E3DRSP_GRAPHICS_EXPORT ShaderDesc
	{
		ShaderDesc(
			const std::string& EntryPoint,
			ShaderType type,
			ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
		);

		std::string EntryPoint;
		ShaderType Type;
		ShaderFeatureLevel FeatureLevel;
	
		virtual ~ShaderDesc() = default;
	};

	struct E3DRSP_GRAPHICS_EXPORT ShaderDescFile : public ShaderDesc
	{
		ShaderDescFile(
			std::filesystem::path FilePath,
			const std::string& EntryPoint,
			ShaderType type,
			ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
		);

		std::filesystem::path FilePath;

		~ShaderDescFile() override = default;
	};

	struct E3DRSP_GRAPHICS_EXPORT ShaderDescSource : public ShaderDesc
	{
		ShaderDescSource(
			const std::string& SourceCode,
			const std::string& EntryPoint,
			ShaderType type,
			ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
		);

		std::string SourceCode;

		~ShaderDescSource() override = default;
	};
}