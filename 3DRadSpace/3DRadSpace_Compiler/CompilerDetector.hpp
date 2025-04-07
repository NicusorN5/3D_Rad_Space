#pragma once

#include "Headers.hpp"

struct Compiler
{
	enum class Type
	{
		/// <summary>
		/// MSVC is invoked by MSBuild that is invoked using devenv.exe.
		/// </summary>
		MSVC, 
		Clang,
		GCC
	} CompilerType;

	std::string Path;
};

/// <summary>
/// Returns compiler path.
/// </summary>
/// <returns></returns>
std::optional<Compiler> FindCompiler();

void SaveCompilerCache(const Compiler& compiler);