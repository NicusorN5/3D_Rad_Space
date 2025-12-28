#pragma once
#include "../Content/ContentManager.h"
#include "../Objects/IObject.h"
#include "../Objects/ObjectList.h"
#include "../Games/Game.h"

#ifdef __cplusplus
extern "C"
{
#endif
	bool E3DRSP_LoadProject(
		E3DRSP_ObjectList* lst,
		E3DRSP_ContentManager* content,
		const char* projectPath
	);

	/// <summary>
	/// Loads a single object from a project file. Used when resetting objects.
	/// </summary>
	/// <param name="path">Path to project.</param>
	/// <param name="id">Object ID.</param>
	/// <returns>Newly allocated object. Must be freed.</returns>
	E3DRSP_IObject E3DRSP_LoadObjectFromProject(const char* path, unsigned id);

	/// <summary>
	/// Saves all the objects and asset data into a 3DRSP file.
	/// </summary>
	/// <param name="lst">Object list.</param>
	/// <param name="content">Content manager.</param>
	/// <param name="projectPath">File to save to.</param>
	/// <returns>True if succeded.</returns>
	static bool E3DRSP_SaveProject(E3DRSP_ObjectList* lst, E3DRSP_ContentManager* content, const char* projectPath);
#ifdef __cplusplus
}
#endif