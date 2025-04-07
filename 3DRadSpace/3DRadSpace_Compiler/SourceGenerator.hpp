#pragma once
#include "CompilerDetector.hpp"

bool GenerateProject(const std::filesystem::path& output, std::vector<std::filesystem::path> files, Compiler::Type type);