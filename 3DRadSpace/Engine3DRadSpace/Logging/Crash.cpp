#include "Crash.hpp"
#include <iostream>
#include "Warning.hpp"

void Engine3DRadSpace::Logging::ReportCrashToFile(const std::exception& e, const std::stacktrace& stacktrace)
{
	std::string stacktraceText = std::format("A {} exception was thrown\r\nException message: {}\r\nStacktrace:\r\n\r\n", typeid(e).name(), e.what());
	for (auto& line : stacktrace)
	{
		stacktraceText += std::to_string(line);
		stacktraceText += "\r\n";
	}

	std::print(std::cerr, "[CRASH] {}", stacktraceText);

	std::ofstream crashFile("crash_report.txt", std::ios::out | std::ios::trunc);
	if (!crashFile.is_open())
	{
		PrintWarning("Failed to open crash report file for writing.");
		return;
	}
	crashFile << stacktraceText;
	crashFile.close();
}