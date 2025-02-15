/// ------------------------------------------------------------------------------------------------
/// File:   Logging/Message.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "Message.hpp"
#include <fstream>
#include <print>
#include <iostream>

using namespace Engine3DRadSpace::Logging;

Message::Message(const int32_t code, const std::string& details, const void* extra) :
	Details(details),
	Code(code),
	Extra(nullptr)
{
}

void Engine3DRadSpace::Logging::SetLastMessage(const Message &msg)
{
	MessageHandler(msg);
}

void Engine3DRadSpace::Logging::SetLastMessage(const std::string& msg)
{
	MessageHandler(Message(0, msg, nullptr));
}

void Engine3DRadSpace::Logging::DefaultMessageHandler(const Message &msg)
{
	std::fstream file("Logs.log", std::ios::app | std::ios::out | std::ios::ate); //create a file stream for writing, with append and seek end flags
	std::println(file, "[INFO]{} Code {}", msg.Details, msg.Code);
	std::println(file, "[INFO]{} Code {}", msg.Details, msg.Code);
	//std::println(std::cout, "\x1B[38;5;3m [INFO]x1B[38;5;7m{} Code {}", msg.Details, msg.Code);
	file.close();
}
FuncMessageHandler Engine3DRadSpace::Logging::MessageHandler = DefaultMessageHandler;
