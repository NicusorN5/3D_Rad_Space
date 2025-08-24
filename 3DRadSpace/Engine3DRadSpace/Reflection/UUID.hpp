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

	template<>
	struct formatter<Engine3DRadSpace::Reflection::UUID>
	{
		constexpr auto parse(std::format_parse_context& ctx) {
			return ctx.begin();
		}

		auto format(const Engine3DRadSpace::Reflection::UUID& uuid, std::format_context& ctx) const {
			return std::format_to(ctx.out(), "{{{:x}-{:x}-{:x}-{:x}{:x}-{:x}{:x}{:x}{:x}{:x}{:x}}}", 
				uuid.Data1,
				uuid.Data2,
				uuid.Data3,
				uuid.Data4[0],
				uuid.Data4[1],
				uuid.Data4[2],
				uuid.Data4[3],
				uuid.Data4[4],
				uuid.Data4[5],
				uuid.Data4[6],
				uuid.Data4[7]
			);
		}
	};
}