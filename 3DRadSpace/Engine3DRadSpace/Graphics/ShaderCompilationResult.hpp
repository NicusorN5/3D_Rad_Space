#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IShader;
	struct ShaderCompilationResult
	{
		IShader* Shader;
		std::string Log;
		bool Succeded;
	};
}