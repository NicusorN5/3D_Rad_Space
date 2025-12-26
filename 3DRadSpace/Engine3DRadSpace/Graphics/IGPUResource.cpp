#include "IGPUResource.hpp"
#include "IGPUResource.h"

using namespace Engine3DRadSpace::Graphics;

E3DRSP_IGraphicsDevice E3DRSP_IGPUResource_GetGraphicsDevice(E3DRSP_IGPUResource* resource)
{
	return reinterpret_cast<E3DRSP_IGraphicsDevice>(reinterpret_cast<IGPUResource*>(resource)->GetGraphicsDevice());
}
	
void* E3DRSP_IGPUResource_GetHandle(E3DRSP_IGPUResource* resource)
{
	return reinterpret_cast<IGPUResource*>(resource)->GetHandle();
}

void E3DRSP_IGPUResource_Destroy(E3DRSP_IGPUResource* resource)
{
	delete reinterpret_cast<IGPUResource*>(resource);
}