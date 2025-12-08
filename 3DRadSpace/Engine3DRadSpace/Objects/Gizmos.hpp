#pragma once
#include "../Objects/Gizmos/Gizmo.hpp"
#include "../Reflection/UUID.hpp"

extern E3DRSP_OBJECTS_EXPORT std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, std::unique_ptr<Engine3DRadSpace::Objects::Gizmos::IGizmo>>> e3drsp_gizmos;

namespace Engine3DRadSpace::Internal
{
	Objects::Gizmos::IGizmo* GizmoOf(const Reflection::UUID& uuid);

	template<Reflection::ReflectableObject O>
	Objects::Gizmos::IGizmo* GizmoOf(const O* object)
	{
		if(object == nullptr) return nullptr;

		auto possibleGizmo = GizmoOf(object->GetUUID());
		if(possibleGizmo != nullptr) return possibleGizmo;

		std::unique_ptr<Engine3DRadSpace::Objects::Gizmos::IGizmo> gizmo;
		gizmo.reset(new Objects::Gizmos::Gizmo<O>());
		auto result = gizmo.get();

		e3drsp_gizmos.emplace_back(
			object->GetUUID(),
			std::move(gizmo)
		);

		return result;
	}
}