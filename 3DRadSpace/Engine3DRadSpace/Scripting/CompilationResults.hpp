#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Scripting
{
	struct CompilationResults
	{
		bool Successful;

		std::string Errors;
		std::string Warnings;
		std::string Messages;
	};
}