#include "../../Core/IService.hpp"
#include "IService.h"

using namespace Engine3DRadSpace;

void E3DRSP_IService_Destroy(E3DRSP_IService* service)
{
	if(service != nullptr)
		delete reinterpret_cast<IService*>(service);
}