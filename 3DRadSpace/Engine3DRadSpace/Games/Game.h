#pragma once
#include "../Core/Libs.h"
#include "../Math/Ray.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"

typedef void* E3DRSP_Game;

#ifdef __cplusplus
extern "C"
{
#endif
	E3DRSP_Game E3DRSP_Game_Create(const char* title, size_t width, size_t height, bool fullscreen);
	
	void E3DRSP_Game_Run(E3DRSP_Game game);
	void E3DRSP_Game_RunOneFrame(E3DRSP_Game game);
	void E3DRSP_Game_Exit(E3DRSP_Game game);

	bool E3DRSP_Game_WasInitialized(E3DRSP_Game game);
	bool E3DRSP_Game_WasLoaded(E3DRSP_Game game);
	E3DRSP_Ray E3DRSP_Game_GetMouseRay(
		E3DRSP_Game game,
		E3DRSP_Vector2 mousePos,
		const E3DRSP_Matrix4x4* view,
		const E3DRSP_Matrix4x4* projection
	);

	void E3DRSP_Game_AppendScene(E3DRSP_Game game, const char* path);
	void E3DRSP_Game_Destroy(E3DRSP_Game game);
#ifdef
}
#endif
