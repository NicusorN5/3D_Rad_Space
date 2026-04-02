#include "Button.h"
#include "../../../Objects/Impl/Button.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_Button E3DRSP_Button_Create()
{
	return new Button();
}