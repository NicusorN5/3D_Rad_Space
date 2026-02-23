#pragma once
#include "Headers.hpp"
#include "ProjectInfo.hpp"

bool MSVC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath);
bool Clang_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath);
bool GCC_Build(const ProjectInfo& project, const std::filesystem::path& compilerPath);