#pragma once
#include "Headers.hpp"
#include "ProjectInfo.hpp"

void MSVC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath);
void Clang_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath);
void GCC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath);