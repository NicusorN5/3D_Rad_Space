#include "Empty.h"
#include "../../../Objects/Impl/Empty.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_Empty E3DRSP_Empty_Create()
{
	return new Empty();
}