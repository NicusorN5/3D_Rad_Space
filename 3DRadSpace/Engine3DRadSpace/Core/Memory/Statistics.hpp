#pragma once
#include "../Libs.h"

namespace Engine3DRadSpace::Memory
{
	class E3DRSP_CORE_EXPORT Statistics
	{
	public:
		static unsigned long long AllocatedBytes;
		static unsigned long long NumAllocations;
	};
}