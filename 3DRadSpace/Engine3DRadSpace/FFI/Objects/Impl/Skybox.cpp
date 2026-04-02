#include "Skybox.h"
#include "../../../Objects/Impl/Skybox.hpp"

using namespace Engine3DRadSpace::Objects;

E3DRSP_Skybox E3DRSP_Skybox_Create()
{
	return new Skybox();
}

unsigned E3DRSP_Skybox_Get(E3DRSP_Skybox skybox)
{
	return static_cast<Skybox*>(skybox)->SkyboxID;
}

void E3DRSP_Skybox_Set(E3DRSP_Skybox skybox, unsigned skyboxID)
{
	static_cast<Skybox*>(skybox)->SkyboxID = skyboxID;
}