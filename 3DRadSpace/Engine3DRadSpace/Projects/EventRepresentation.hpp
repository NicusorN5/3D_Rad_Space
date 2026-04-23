#pragma once
#include "../Reflection/Event.hpp"

namespace Engine3DRadSpace::Objects
{
	class ObjectList;
}

namespace Engine3DRadSpace::Projects
{
	/// <summary>
	/// Serializable representation of an <see cref="Event"/>.
	/// </summary>
	struct EventRepresentation
	{
		size_t OwnerObject;
		size_t FunctionID;
		std::vector<std::any> Arguments;
		bool IsMethod;

		std::optional<Reflection::Event> Reconstruct(Objects::ObjectList* list) const;
	};
}