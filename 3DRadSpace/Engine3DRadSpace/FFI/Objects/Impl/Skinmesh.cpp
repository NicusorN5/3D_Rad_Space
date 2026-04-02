#include "Skinmesh.h"
#include "../../../Objects/Impl/Skinmesh.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_Skinmesh E3DRSP_Skinmesh_Create()
{
	return new Skinmesh();
}

unsigned E3DRSP_Skinmesh_GetModel(E3DRSP_Skinmesh skinmesh)
{
	return static_cast<Skinmesh*>(skinmesh)->Model.ID;
}

void E3DRSP_Skinmesh_SetModel(E3DRSP_Skinmesh skinmesh, unsigned modelID)
{
	static_cast<Skinmesh*>(skinmesh)->Model.ID = modelID;
}