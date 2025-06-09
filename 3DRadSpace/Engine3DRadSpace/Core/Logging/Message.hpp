#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct E3DRSP_CORE_EXPORT Message
	{
		const std::string Details;
		int32_t Code;
		const void *Extra;

		Message(const int32_t code, const std::string& details, const void* extra = nullptr);
	};

	typedef void (*FuncMessageHandler)(const Message& warning);
	extern FuncMessageHandler MessageHandler;

	void E3DRSP_CORE_EXPORT SetLastMessage(const Message &warning);
	void E3DRSP_CORE_EXPORT SetLastMessage(const std::string& msg);
	void E3DRSP_CORE_EXPORT DefaultMessageHandler(const Message &warning);
}