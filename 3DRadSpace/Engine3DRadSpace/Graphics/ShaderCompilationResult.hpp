#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct ShaderCompilationResult
	{
		std::string Log;
		bool Succeded;
		std::string Identifier;
	};
}