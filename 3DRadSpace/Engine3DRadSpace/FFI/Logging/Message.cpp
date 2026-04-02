#include "Message.h"
#include "../../Logging/Message.hpp"

using namespace Engine3DRadSpace::Logging;

void E3DRSP_SetLastMessage(const E3DRSP_Message* message)
{
	SetLastMessage(Message(
		message->Code,
		message->Details,
		message->Extra
	)
	);
}