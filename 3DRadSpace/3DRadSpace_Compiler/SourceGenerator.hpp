#pragma once
#include "CompilerDetector.hpp"
#include "ProjectInfo.hpp"

bool GenerateProject(const ProjectInfo &info, std::vector<std::filesystem::path> files, Compiler::Type type);