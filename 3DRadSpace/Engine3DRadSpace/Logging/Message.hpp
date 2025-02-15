/// ------------------------------------------------------------------------------------------------
/// File:   Logging/Message.hpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
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
	void SetLastMessage(const std::string& msg);
	void DLLEXPORT DefaultMessageHandler(const Message &warning);
}