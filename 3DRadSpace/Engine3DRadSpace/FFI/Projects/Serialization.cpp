#include "../../Projects/Serialization.hpp"
#include "Serialization.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Internal;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

bool E3DRSP_LoadProject(
	E3DRSP_ObjectList* lst,
	E3DRSP_ContentManager* content,
	const char* projectPath
)
{
	return Engine3DRadSpace::Projects::Serializer::LoadProject(
		reinterpret_cast<Engine3DRadSpace::Objects::ObjectList*>(lst),
		reinterpret_cast<Engine3DRadSpace::Content::ContentManager*>(content),
		std::filesystem::path(projectPath)
	);
}

E3DRSP_IObject E3DRSP_LoadObjectFromProject(const char* path, unsigned id)
{
	return static_cast<E3DRSP_IObject>(Engine3DRadSpace::Projects::Serializer::LoadObjectFromProject(
		std::filesystem::path(path),
		id
	));
}

bool E3DRSP_SaveProject(E3DRSP_ObjectList* lst, E3DRSP_ContentManager* content, const char* projectPath)
{
	return Engine3DRadSpace::Projects::Serializer::SaveProject(
		reinterpret_cast<Engine3DRadSpace::Objects::ObjectList*>(lst),
		reinterpret_cast<Engine3DRadSpace::Content::ContentManager*>(content),
		std::filesystem::path(projectPath)
	);
}