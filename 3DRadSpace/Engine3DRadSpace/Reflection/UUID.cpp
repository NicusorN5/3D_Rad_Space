/// ------------------------------------------------------------------------------------------------
/// File:   Reflection/UUID.cpp
/// Copyright (C) 2025, 3DRadSpace
/// License: CC0-1.0 license
/// ------------------------------------------------------------------------------------------------
#include "UUID.hpp"
#include "../Libs.hpp"

Engine3DRadSpace::Reflection::UUID Engine3DRadSpace::Reflection::UUID::New()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 0xFF);

	Engine3DRadSpace::Reflection::UUID uuid;
	
	unsigned char* ptr = reinterpret_cast<unsigned char*>(&uuid);
	for(int i = 0; i < sizeof(Engine3DRadSpace::Reflection::UUID); i++)
	{
		ptr[i] = static_cast<unsigned char>(dis(gen));
	}

	 ptr[6] = ((ptr[6] & 0x0f) | 0x40); // Version 4
     ptr[8] = ((ptr[8] & 0x3f) | 0x80); // Variant is 10

	 return uuid;

}