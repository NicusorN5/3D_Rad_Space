#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Scripting
{
	struct CompilationResults
	{
		bool Successful;

		const char* Errors;
		const char* Warnings;
		const char* Messages;
	};
}