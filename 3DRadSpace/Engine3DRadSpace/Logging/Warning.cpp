/// ------------------------------------------------------------------------------------------------
/// File:   Logging/Warning.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Warning.hpp"
#include <fstream>
#include <print>
#include <iostream>

using namespace Engine3DRadSpace::Logging;

Warning::Warning(const int32_t code,const int severity) : 
	Details(std::format("Warning code {} severity {}",code,severity)),
	Code(code),
	Severity(severity),
	Extra(nullptr)
{
}

Warning::Warning(const int32_t code, const std::string& details, const int severity, const void* extra) :
	Details(details),
	Code(code),
	Severity(severity),
	Extra(nullptr)
{
}

void Engine3DRadSpace::Logging::SetLastWarning(const Warning &warning)
{
	WarningHandler(warning);
}

void Engine3DRadSpace::Logging::SetLastWarning(const std::string& warning_text)
{
	WarningHandler(Warning(0, warning_text, 0, nullptr));
}

void Engine3DRadSpace::Logging::DefaultWarningHandler(const Warning &warning)
{
	std::fstream file("Warnings.log", std::ios::app | std::ios::out | std::ios::ate); //create a file stream for writing, with append and seek end flags
	std::println(file, "[WARNING] {} Code {} Severity {}", warning.Details, warning.Code, warning.Severity);
	std::println(file, "[WARNING] {} Code {} Severity {}", warning.Details, warning.Code, warning.Severity);
	//std::println(std::cout, "\x1B[38;5;3m [WARNING] {}x1B[38;5;7m Code {} Severity {}", warning.Details, warning.Code, warning.Severity);
	file.close();
}
FuncWarningHandler Engine3DRadSpace::Logging::WarningHandler = DefaultWarningHandler;
