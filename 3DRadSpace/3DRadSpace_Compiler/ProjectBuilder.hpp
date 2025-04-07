#pragma once
#include "Headers.hpp"

void MSVC_Build(const std::filesystem::path& outputFolder, const std::filesystem::path& compilerPath);
void Clang_Build(const std::filesystem::path& outputFolder, const std::filesystem::path& compilerPath);
void GCC_Build(const std::filesystem::path& outputFolder, const std::filesystem::path& compilerPath);