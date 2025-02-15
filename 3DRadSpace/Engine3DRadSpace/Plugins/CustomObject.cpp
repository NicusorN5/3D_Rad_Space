/// ------------------------------------------------------------------------------------------------
/// File:   Plugins/CustomObject.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "CustomObject.hpp"
#include "../Logging.hpp"

using namespace Engine3DRadSpace::Plugins;

extern std::vector<Engine3DRadSpace::Reflection::ReflectedObject*> _3drsp_internal_objects_list;

void Engine3DRadSpace::Plugins::LoadCustomObjectsFromLibHandle(void* libraryHandle)
{
	LoadCustomObjects loadCustomObjects = nullptr;
#ifdef _WIN32
	loadCustomObjects = reinterpret_cast<LoadCustomObjects>(GetProcAddress(static_cast<HMODULE>(libraryHandle), "LoadCustomObjects"));
#elif _LINUX
	auto loadCustomObjects = reinterpret_cast<LoadCustomObjects>(dlsym(libraryHandle, "LoadCustomObjects"));
#endif
	if(loadCustomObjects)
	{
		auto objects = loadCustomObjects();

		for(auto& object : objects)
		{
			//avoid repeating UUIDs. O(n^2) but hopefully the number of custom objects is small.
			for(auto& internalObject : _3drsp_internal_objects_list)
			{
				//if UUIDs are in conflicting, generate a new UUID. Used a while loop in case there's two consecutive UUIDs that are the same.
				while(internalObject->ObjectUUID == object->ObjectUUID)
				{
					object->ObjectUUID = Reflection::UUID::New();

					std::string warning = "Conflicting UUIDs for";
					warning += object->Name + " and " + internalObject->Name;
					Logging::SetLastWarning(Logging::Warning(2001, warning.c_str(), 1, nullptr));
				}
			}

			_3drsp_internal_objects_list.push_back(object);
			Logging::SetLastMessage(Logging::Message(1000, "Loaded custom object " + object->Name, nullptr));
		}
	}
}