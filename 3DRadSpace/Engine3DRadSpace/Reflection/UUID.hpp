#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Reflection
{
	struct UUID
	{
		unsigned long  Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[8];

		bool operator ==(const UUID &) const = default;
		bool operator !=(const UUID &) const = default;

		static UUID New();
	};
}

namespace std
{
	template<>
	struct hash<Engine3DRadSpace::Reflection::UUID>
	{
		size_t operator()(const Engine3DRadSpace::Reflection::UUID &uuid) const noexcept
		{
			size_t h = 0;
			h ^= uuid.Data1;
			h ^= uuid.Data2;
			h ^= uuid.Data3;
			for (int i = 0; i < 8; i++)
			{
				h ^= uuid.Data4[i];
			}
			return h;
		}
	};
}