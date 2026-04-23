#include "EventRepresentation.hpp"
#include "../Objects/ObjectList.hpp"
#include "../Objects/Impl/Objects.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Objects;

std::optional<Event> EventRepresentation::Reconstruct(ObjectList* list) const
{
	Event e;
	auto obj = list->operator[](OwnerObject);
	auto reflObject = Internal::GetReflDataFromUUID(obj->GetUUID());
	size_t id = 0;
	bool assigned = false;

	if(IsMethod)
	{
		e.SetObject(obj);
	}

	for (auto& f : *reflObject)
	{
		auto fn = dynamic_cast<IReflectedFunction*>(f);
		if (fn == nullptr) continue;

		if (id++ == FunctionID)
		{
			e.Bind(fn);
			assigned = true;
			break;
		}
	}

	if (!assigned)
	{
		return std::nullopt;
	}

	return e;
}