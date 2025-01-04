#include "Message.hpp"
#include <fstream>

using namespace Engine3DRadSpace::Logging;

Message::Message(const int32_t code,const int severity) : 
	Details(std::format("Warning code {} severity {}",code,severity)),
	Code(code),
	Extra(nullptr)
{
}

Message::Message(const int32_t code, const std::string& details, const int severity, const void* extra) :
	Details(details),
	Code(code),
	Extra(nullptr)
{
}

void Engine3DRadSpace::Logging::SetLastMessage(const Message &msg)
{
	MessageHandler(msg);
}

void Engine3DRadSpace::Logging::DefaultMessageHandler(const Message &msg)
{
	std::fstream file("Logs.log", std::ios::app | std::ios::out | std::ios::ate); //create a file stream for writing, with append and seek end flags
	file << "[INFO]"<< msg.Details << " Code " << msg.Code << std::endl; //new line + flush
	file.close();
}
FuncMessageHandler Engine3DRadSpace::Logging::MessageHandler = DefaultMessageHandler;
