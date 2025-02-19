#include "CustomObject.hpp"
#include "../Logging.hpp"
#include "OS.hpp"

using namespace Engine3DRadSpace::Plugins;

extern std::vector<Engine3DRadSpace::Reflection::ReflectedObject*> _3drsp_internal_objects_list;

void Engine3DRadSpace::Plugins::LoadCustomObjectsFromLibHandle(void* libraryHandle)
{
	LoadCustomObjects loadCustomObjects = Plugins::GetFunctionFromLibrary<LoadCustomObjects>(libraryHandle, "LoadCustomObjects");
	if(loadCustomObjects)
	{
		auto objects = loadCustomObjects();

		for(auto& object : objects)
		{
			bool ok = true;

			//avoid repeating UUIDs. O(n^2) but hopefully the number of custom objects is small.
			for(auto& internalObject : _3drsp_internal_objects_list)
			{
				//if UUIDs are in conflicting throw an exception. We can't guarantee serialization when saving or loading... Skip this object...
				if(internalObject->ObjectUUID == object->ObjectUUID)
				{					
					Logging::SetLastWarning(std::format("Conflicting UUIDs for {} and {}. ", object->Name, internalObject->Name));
					ok = false;
					break;
				}
			}

			if(!ok) continue;

			_3drsp_internal_objects_list.push_back(object);
			Logging::SetLastMessage(Logging::Message(1000, "Loaded custom object " + object->Name, nullptr));
		}
	}
}