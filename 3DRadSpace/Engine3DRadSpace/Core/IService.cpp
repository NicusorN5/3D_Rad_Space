#include "IService.hpp"
#include "IService.h"

using namespace Engine3DRadSpace;

void E3DRSP_IService_Destroy(E3DRSP_IService* service)
{
	assert(service != nullptr);
	delete reinterpret_cast<IService*>(service);
}