#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct DLLEXPORT Message
	{
		const std::string Details;
		int32_t Code;
		const void *Extra;

		Message(const int32_t code, const std::string& details, const void* extra = nullptr);
	};

	typedef void (*FuncMessageHandler)(const Message& warning);
	extern FuncMessageHandler MessageHandler;

	void DLLEXPORT SetLastMessage(const Message &warning);
	void DLLEXPORT SetLastMessage(const std::string& msg);
	void DLLEXPORT DefaultMessageHandler(const Message &warning);
}