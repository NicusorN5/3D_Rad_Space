#include "Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Internal;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;
using namespace Engine3DRadSpace::Reflection;

std::vector<std::pair<Reflection::UUID, std::unique_ptr<IGizmo>>> _3drsp_gizmos;

IGizmo* Engine3DRadSpace::Internal::GizmoOf(const Reflection::UUID& uuid)
{
	for(auto& [g_uuid, gizmo] : _3drsp_gizmos)
	{
		if(g_uuid == uuid)
			return gizmo.get();
	}
	return nullptr;
}
