#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Reflection
{
	#pragma warning(push)
	#pragma warning(disable:26495)
		struct EnumEntry
		{
			std::string VisibleName;
			int64_t Value;
		};
	#pragma warning(pop)
}