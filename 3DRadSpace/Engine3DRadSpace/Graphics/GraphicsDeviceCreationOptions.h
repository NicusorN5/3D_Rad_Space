#pragma once

enum E3DRSP_GraphicsDeviceCreationOptions
{
	E3DRSP_GDCO_Unspecified = 0,
	E3DRSP_GDCO_Debug = 1 << 0,
	E3DRSP_GDCO_Singlethreaded = 1 << 1,
	E3DRSP_GDCO_SelectGPU_Performance = 1 << 2,
	E3DRSP_GDCO_SelectGPU_Integrated = 1 << 3,
	E3DRSP_GDCO_SelectGPU_Software = 1 << 4,
	E3DRSP_GDCO_SelectGPU_Default = 1 << 5
};